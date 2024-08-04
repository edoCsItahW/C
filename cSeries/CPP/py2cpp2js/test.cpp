// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: bridging
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/04 上午11:27
 * @Commend:
 *******************************************************/
#include <napi.h>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <iostream>


namespace py = pybind11;
namespace node = Napi;


node::String pyVersion(const node::CallbackInfo& info) {
	py::scoped_interpreter guard{};

	py::module sys = py::module_::import("sys");

	py::module builtins = py::module_::import("builtins");

	try {
		std::cout << builtins.attr("object").attr("__doc__").cast<std::string>() << std::endl;
	}
	catch (py::error_already_set& e) {
		node::Error::New(info.Env(), e.what()).ThrowAsJavaScriptException();
	}

	return node::String::New(info.Env(), sys.attr("version").cast<std::string>());
}

node::Object Init(node::Env env, node::Object exports) {
	exports.Set(node::String::New(env, "pyVersion"), node::Function::New(env, pyVersion));
	return exports;
}


NODE_API_MODULE(hello, Init)
