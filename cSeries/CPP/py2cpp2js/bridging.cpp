// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: EXTENT
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/02 上午2:41
 * @Commend:
 *******************************************************/
//#include "py/PyObject.h"
#include <napi.h>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <map>
#include <iostream>
#include <any>
#include "py/funcKit.h"

#define DEBUG true

void debug(const std::string& msg = "") {
	if (DEBUG)
		std::cout << msg << " -> ";
}

template<typename ...Args>
void debug(const std::string& name, Args&&... args) {
	if (DEBUG) {
		std::cout << name << "(";
		int i = 0;
		((std::cout << args << (i++ == sizeof...(args) - 1 ? "" : ", ")), ...);
		std::cout << ") -> ";
	}
}

using namespace FuncKit;

py::scoped_interpreter guard{};
/**
 * @brief 缓存python类的InsMap的实例
 * @note 获取类时请使用该实例,而非重新从builtins中导入.
 */
InsMap* INS_CACHE = new InsMap();


/**
 * @brief 获取python属性
 * @tparam T 确定该返回属性的类型(父类必须为py::object)
 * @param type python类的名称,该名称将作为键在python的builtins中查找并导入对应的类.
 * @param key 需要从该类中获取的属性名称.
 * @return 类型属性值
 */
template<isChildOf<py::object> T = py::object>
py::object getPyAttr(const char* type, const char *key) {
	debug("getPyAttr", type, key);
	PyAttr obj = INS_CACHE->get(type);
	return obj.attr(key).cast<T>();
}


/**
 * @brief 属性map类
 * @property objType python类的名称
 * @property thisObj js类的this指针
 */
class AttrMap : public std::map<const char*, Napi::Value> {
	private:
		const char* objType;
		Napi::Object thisObj;

	public:
	    explicit AttrMap(Napi::Object thisObj, const char* type) : std::map<const char*, Napi::Value>(), objType(type), thisObj(thisObj) {
			debug("AttrMap", type);
		}

		template<typename T, isChildOf<Napi::Value> U = Napi::Value>
		/**
		 * @brief 获取属性值
		 * @tparam T 将从getPyAttr获取的python属性值明确为T(cpp类型)类型.
		 * @tparam U 将cpp类型转换为js类型,并返回U类型.
		 * @param key 需要从该类中获取的属性名称.
		 * @details 由于该类是python-cpp-js的交互接口类,需要将从getPyAttr获取的python属性值
		 * 转换为cpp类型再转换成js类型,然后存入map,因此需要使用模板进行多次类型转换.get方法隐含了
		 * set操作,因此获取未设置的属性时会自动设置.
		 * @note 该重载实现使用通用转换,也许并不安全.
		 * @return 类型属性值
		 */
		U get(const char* key) {
			debug("AttrMap::get<T, U>", key);
			if (find(key) == end()) {
				this->insert(std::make_pair(key, Napi::Value::From(thisObj.Env(), getPyAttr(objType, key).cast<T>()).template As<U>()));
			}
			return this->at(key).As<U>();
		}

		template <typename T = std::any, Py2CppFn<T> CppTrans, Cpp2JsFn<T> JsTrans>
		/**
		 * @brief 获取属性值
		 * @tparam T 用于辅助检查的转换中间值类型(cpp类型)
		 * @tparam CppTrans 转换python属性值到cpp类型的函数模板.
		 * @tparam JsTrans 转换cpp类型到js类型的函数模板.
		 * @param key 需要从该类中获取的属性名称.
		 * @details 该重载实现使用模板参数化,可以指定转换函数模板,并检查返回类型是否与T一致.
		 * @note 该重载实现使用模板参数化,安全性取决于转换函数模板的正确性.
		 * @return 类型属性值
		 */
		auto get(const char* key) {
			debug("AttrMap::get<T, CppTrans, JsTrans>", key);
			if (find(key) == end()) {
				this->insert(std::make_pair(key, JsTrans(CppTrans(getPyAttr(objType, key)))));
			}
			return this->at(key).As<JsTrans>();
		}

		template<isChildOf<Napi::Value> T = Napi::Value>
		/**
		 * @brief 设置属性值
		 * @tparam T 值类型
		 * @param key 属性名称
		 * @param value 属性值
		 * @details 该方法设置属性值,并将属性值存入map,并将属性值设置到js类对象中.
		 */
		void set(const char* key, const T& value) {
			debug("AttrMap::set<T>", key, value);
			this->insert(std::make_pair(key, value));
		}
};


class ObjectAdapter : public Napi::ObjectWrap<ObjectAdapter> {
	protected:
		AttrMap attrs;

	public:
		explicit ObjectAdapter(const Napi::CallbackInfo &info);  // [外部调用]python的Object类不允许传入参数,如非空应抛出异常.
		static Napi::Object Init(Napi::Env env, Napi::Object exports);

		template<typename T, isChildOf<Napi::Value> U = Napi::Value>
		Napi::Value get(const Napi::CallbackInfo& info);

		template<isChildOf<Napi::Value> T = Napi::Value>
		void set(const Napi::CallbackInfo& info, const Napi::Value& value);
};


ObjectAdapter::ObjectAdapter(const Napi::CallbackInfo& info)
	: ObjectWrap(info), attrs(info.This().As<Napi::Object>(), "object") {
	debug("ObjectAdapter");
	if (info.Length())
		Napi::TypeError::New(info.Env(), "object() takes no arguments").ThrowAsJavaScriptException();

	Napi::String doc = attrs.get<std::string, Napi::String>("__doc__");
//	Napi::Object p = Napi::Object::New(info.Env());
//	p.Set("__doc__", doc);
	info.This().As<Napi::Object>().Set("__doc__", doc);
}

template<typename T, isChildOf<Napi::Value> U>
Napi::Value ObjectAdapter::get(const Napi::CallbackInfo& info) {
//	debug("ObjectAdapter::get<T, U>", info[0].As<Napi::String>().Utf8Value().data());
//	if (info.Length() != 1)
//		std::cout << "get() takes exactly one argument, and you have " << info.Length() << std::endl;
//	else
//		node::TypeError::New(info.Env(), "get() takes exactly one argument").ThrowAsJavaScriptException();
	return attrs.get<T, U>(info[0].As<Napi::String>().Utf8Value().data());
//	return Napi::Object(info.Env(), nullptr);
}

template<isChildOf<Napi::Value> T>
void ObjectAdapter::set(const Napi::CallbackInfo& info, const Napi::Value& value) {
	debug("ObjectAdapter::set<T>", info[0].IsObject(), value.IsObject(), info.Length());
	if (info[0].IsString())
		std::cout << info[0].As<Napi::String>().Utf8Value() << std::endl;
	if (value.IsString())
		std::cout << value.As<Napi::String>().Utf8Value() << std::endl;
//	if (info[0].IsObject()) {
//		auto obj = info[0].As<Napi::Object>();
//		for (auto it : obj.GetPropertyNames()) {
//			auto key = Napi::Value(it.second).As<Napi::String>().Utf8Value();
//			std::cout << key << std::endl;
//			std::cout << obj.Get(key).As<Napi::String>().Utf8Value() << std::endl;
//		}
//	}
//	if (value.IsObject()) {
//		auto obj = info[0].As<Napi::Object>();
//		for (auto it : obj.GetPropertyNames())
//			std::cout << Napi::Value(it.second).As<Napi::String>().Utf8Value().data() << std::endl;
//	}

//	if (info.Length() != 1)
//		std::cout << "set() takes exactly two arguments, and you have " << info.Length() << std::endl;
//	else
////		node::TypeError::New(info.Env(), "set() takes exactly two arguments").ThrowAsJavaScriptException();
////		attrs.set<T>(info[0].As<node::String>().Utf8Value().data(), value.As<T>());
//		attrs.set<T>(info[0].As<Napi::String>().Utf8Value().data(), value.As<T>());
}


Napi::Object ObjectAdapter::Init(Napi::Env env, Napi::Object exports) {
	char doc[8] = "__doc__";
	Napi::Function func = DefineClass(
		env,
		"PyObject",
		{
			InstanceAccessor(
				"__doc__",
				&ObjectAdapter::get<std::string, Napi::String>,
//				&ObjectAdapter::set<Napi::String>,
				nullptr,
				napi_property_attributes::napi_default,
				doc
				)
		}
);
	exports.Set("PyObject", func);
	return exports;
}


Napi::Object Init(Napi::Env env, Napi::Object exports) {
	ObjectAdapter::Init(env, exports);
	return exports;
}

NODE_API_MODULE(bridging, Init)
