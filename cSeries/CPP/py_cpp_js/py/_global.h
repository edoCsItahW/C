// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: py_cpp_js
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/20 下午7:25
 * @Commend:
 *******************************************************/

#ifndef PY_CPP_JS__GLOBAL_H
#define PY_CPP_JS__GLOBAL_H

#include <napi.h>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <vector>
#include <iostream>
#include <map>
#include <functional>
#include <source_location>
#include <sstream>
#include <ranges>
#include <optional>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <typeindex>
#include <optional>
#include <variant>

namespace py = pybind11;
namespace node = Napi;

namespace Global {
	// 全局python环境
	extern py::scoped_interpreter guard;

	/* 全局python内建模块 */
	extern py::module builtins;

	extern py::function dir;
}

namespace Error {
	void NotImplementedError(node::Env env, const std::string& msg);

	void ArgumentError(node::Env env, const std::string& msg);

	/**
	 * 在C++中实现单例模式，通常需要确保以下几点：
	 *
	 *	构造函数和析构函数是私有的，以防止外部实例化。
	 *	拷贝构造函数和赋值运算符是私有的，以防止拷贝和赋值。
	 *	提供一个静态方法来获取单例实例。
	 *	使用一个静态成员变量来存储唯一的实例。
	 *	以下是一个简单的单例模式实现示例：
	 */
	class Try {
		private:
		node::Env _env = nullptr;
		explicit Try(node::Env env);
		explicit Try();
		~Try();

		public:
		static Try& getInstance(node::Env env);
		static Try& getInstance();
		Try(const Try&) = delete;
		void operator=(const Try&) = delete;
		template <typename R, typename... Args>
		std::function<R(Args...)> operator()(R(*f)(Args...), std::source_location loc = std::source_location::current());
		template <typename R, typename... Args>
		std::function<R(Args...)> operator()(R(*f)(Args...), node::Env env, std::source_location loc = std::source_location::current());
	};

	extern Try& try_;
}

namespace Py {
	namespace Tools {
		std::string getPyType(const py::object& value);

		py::list getAttr(const py::object& obj);

		py::tuple getArgs(const node::CallbackInfo& info);
	}
	namespace Converter {
		node::Value pyToJsI(node::Env env, const py::object &value);

		node::String str(node::Env env, const py::object& value);
		node::Number integer(node::Env env, const py::object& value);
		node::Number float_(node::Env env, const py::object& value);
		node::Boolean boolean(node::Env env, const py::object& value);
		node::Array list(node::Env env, const py::object& value);
		node::Object dict(node::Env env, const py::object& value);
		node::Function function(node::Env env, const py::object& value);
		node::Function class_(node::Env env, const py::object& value, const std::string& type);
		/**
	     * @brief 该函数用于将py模块转为js模块(实则为js对象)
	     * @param env node环境
	     * @param value py模块
	     * @return js模块
	     * @note 由于该函数使用递归实现,可能会导致栈溢出,对于大型模块,可能需要使用循环或迭代的方式实现.
	     * */
		node::Object module(node::Env env, const py::object& value);
		node::Value none(node::Env env);

		node::Value pyToJsR(node::Env env, const py::object &value);
	}
}

namespace Js::Converter {
	py::object jsToPy(const node::Value& value);

	py::str string(const node::Value& value);
	py::int_ integer(const node::Value& value);
	py::float_ number(const node::Value& value);
	py::bool_ boolean(const node::Value& value);
	py::list array(const node::Value& value);
	py::dict object(const node::Value& value);
	py::function function(const node::Value& value);
	py::none null(const node::Value& value);
}

namespace Api {
	node::Value import_(const node::CallbackInfo& info);

	void atexit(const node::CallbackInfo& info);
}

#endif // PY_CPP_JS__GLOBAL_H
