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
#include <iostream>
#include <napi.h>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>


namespace py = pybind11;


class pyBridging {
	private:
	py::scoped_interpreter *interp;

	public:
	pyBridging() { interp = new py::scoped_interpreter(); }

	static py::module import(const char *name) { return py::module::import(name); }

	void test() {
		py::module sys = import("sys");

		auto version = sys.attr("version_info").cast<std::string>();

		std::cout << "Python version: " << version << std::endl;
	}
};


class jsBridging : public Napi::ObjectWrap<jsBridging> {
	private:
	static Napi::FunctionReference constructor;
	pyBridging *pb;

	static void test(const Napi::CallbackInfo &info) {
		pyBridging *pb = Napi::ObjectWrap<pyBridging>::Unwrap(info.This().As<Napi::Object>());
		pb->test();
	}

	public:
	static Napi::Object Init(Napi::Env env, Napi::Object exports) {}

	explicit jsBridging(const Napi::CallbackInfo &callbackInfo, const Napi::CallbackInfo &info)
		: ObjectWrap(callbackInfo) {
		pb = new pyBridging();
	}

	void test() { pb->test(); }

	Napi::Object Init(Napi::Env env, Napi::Object exports) {
		Napi::HandleScope scope(env);

		Napi::Function func = DefineClass(env, "jsBridging", {InstanceMethod("test", &jsBridging::test)});

		constructor = Napi::Persistent(func);
		constructor.SuppressDestruct();

		exports.Set("jsBridging", func);
		return exports;
	}

	~jsBridging() override = default;
};
