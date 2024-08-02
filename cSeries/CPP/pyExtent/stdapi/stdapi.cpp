// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: calculator
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/09 下午9:24
 * @Commend:
 *******************************************************/
#include "stdapi.h"


string boolToString(bool value) {
	return value? "True" : "False";
}


PYBIND11_MODULE(stdapi, m) {
	py::class_<String>(m, "String")
	    .def(py::init<>())
		.def(py::init<const string&>(), "Construct a String object from a string", py::arg("value"))
		.def(py::init<int>(), "Construct a String object from an integer", py::arg("value"))
		.def(py::init<bool>(), boolToString, "Construct a String object from a boolean", py::arg("value"))
		.def_property_readonly("value", &String::getInput)
		.def("__str__", [](const String& self) { return string(self); })
		.def("__repr__", [](const String& self) { return "String(" + string(self) + ")"; });
}
