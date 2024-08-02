// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: FILESIZE
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/24 下午11:11
 * @Commend:
 *******************************************************/
#include <pybind11/pybind11.h>
#include <boost/python.hpp>
#include <iostream>

namespace py = pybind11;

void hello() {
	std::cout << "Hello from C++!" << std::endl;
}

void boostHello() {
	try {
		boost::python::object builtins = boost::python::import("__builtin__");

		boost::python::object printFunc = builtins.attr("print");

		printFunc("Hello from Boost.Python!");

	}
	catch (boost::python::error_already_set&) {
		PyErr_Print();
	}
}

PYBIND11_MODULE(combine, m) {
	m.def("hello", &hello, "A function that prints hello");
	m.def("boostHello", &boostHello, "A function that prints hello from Boost.Python");
}
