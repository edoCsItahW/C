// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*
 目标:
	 export function setToJson(data: any): any;
	 export function setToJson(key: string, value: any): any
	 export function setToJson(arg1: any, arg2?: any) {
	 if (arg2 === undefined) {
		const stack = [arg1];

	 while (stack.length) {
	 const current = stack.pop();

	 if (Array.isArray(current)) {
	 current.reverse();

	 while (current.length) {
	  let item = current.pop();

	  if (item instanceof Set)
		item = Array.from(item);

	  else if (typeof item === 'object' && item !== null)
		stack.push(item);

	  else
		  if (!current.length)
		current.reverse();

	  if (Array.isArray(current))
		stack.push(item);

	 }
	 }

	 else if (typeof current === 'object' && current !== null) {
	 Object.entries(current).forEach(([k, v]) => {
	  if (v instanceof Set)
		current[k] = Array.from(v);

	  else if (typeof v === 'object' && v !== null)
		stack.push(v);

	  else
		current[k] = v;
	 })
	 }

	 }
	 return arg1;
	 }
	 else {
	 if (arg2 instanceof Set)
	 return Array.from(arg2)
		else if (typeof arg2 === 'object' && arg2 !== null)
			return Object.entries(arg2).map(([k, v]) => [k, setToJson(k, v)]);
	 return arg2;
	 }

	 }
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <napi.h>
//#include <node.h>
//#include <node_api.h>


// 辅助面向JS函数的CPP函数
namespace cpp {
	using JsValueArr = std::vector<Napi::Value>;

	bool instanceof(const Napi::Value& value, const std::string& type) {

		auto constructor = value.Env().Global().Get(type).As<Napi::Function>();

		return value.As<Napi::Object>().InstanceOf(constructor);
	}

	JsValueArr toCppArr(const Napi::Array& arr) {
		std::vector<Napi::Value> vec;

		for (size_t i = 0; i < arr.Length(); i++)
			vec.push_back(arr.Get(i));

		return vec;
	}

	Napi::Array toJsArr(const JsValueArr& vec) {
		Napi::Env env = vec[0].Env();
		Napi::Array arr = Napi::Array::New(env, vec.size());

		for (size_t i = 0; i < vec.size(); i++)
			arr.Set(i, vec[i]);

		return arr;
	}
}


// 面向JS的函数
namespace JS {
	Napi::Value setToJson(const Napi::CallbackInfo &info) {
		Napi::Env env = info.Env();

		Napi::Value data = info[0];
		std::vector<Napi::Value> stack = {data};

		while (!stack.empty()) {
			Napi::Value current = stack.back();
			stack.pop_back();

			if (current.IsArray()) {
				cpp::JsValueArr currentArr = cpp::toCppArr(current.As<Napi::Array>());
				std::reverse(currentArr.begin(), currentArr.end());

				while (!currentArr.empty()) {
					Napi::Value item = currentArr.back();

					if (cpp::instanceof(item, "Set")) {
						auto tmpArr = item.As<Napi::Array>();
						item = tmpArr.As<Napi::Value>();
					}

					else if (item.IsObject() && !item.IsNull())
						stack.push_back(item);

					else
						if (currentArr.empty())
						    std::reverse(currentArr.begin(), currentArr.end());

					if (current.IsArray())
						stack.push_back(item);

				}
			}

			else if (current.IsObject() && !current.IsNull())
				for (auto [k, v] : current.As<Napi::Object>()) {
					Napi::Value value = v;

					if (cpp::instanceof(v, "Set"))
						current.As<Napi::Object>().Set(k, value.As<Napi::Array>());

					else if (value.IsObject() && !value.IsNull())
						stack.push_back(v);

					else
						current.As<Napi::Object>().Set(k, v);

				}
		}
		return data;
	}
}
Napi::Array setToArr(const Napi::Env& env, const Napi::Value& value) {
	if (cpp::instanceof(value, "Set")) {
		std::cout << "is set" << std::endl;
		return value.As<Napi::Array>();
	}
	else
		std::cout << "not set" << std::endl;
	return Napi::Array::New(env, 0);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	exports.Set(Napi::String::New(env, "setToJson"), Napi::Function::New(env, setToArr));
	return exports;
}

NODE_API_MODULE(addon, Init);

