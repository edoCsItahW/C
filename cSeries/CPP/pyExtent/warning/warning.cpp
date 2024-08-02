// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: C
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/03 下午10:40
 * @Commend:
 *******************************************************/
#include "warning.h"
#include "pybind11/pybind11.h"

namespace py = pybind11;


typedef void (*warnColor)(WarnLevel level, const char* format, ...);


using namespace std;


PYBIND11_MODULE(warning, m) {
	m.doc() = "warning api for python";

	py::enum_<WarnLevel>(m, "WarnLevel")
	    .value("DEBUG", WarnLevel::DEBUG)
	    .value("INFO", WarnLevel::INFO)
	    .value("WARNING", WarnLevel::WARNING)
	    .value("ERROR", WarnLevel::ERROR_)
	    .value("CRITICAL", WarnLevel::CRITICAL)
		.export_values();

	m.def("warn", [](WarnLevel level, const char* msg) {
			  ::warn(level, msg);
	}, "warn function",
		  py::arg("level"), py::arg("msg"));

	m.def("warnColor", [](WarnLevel level, const char* msg) {
			  warnColor(level, msg);
	 }, "warnColor function",
		  py::arg("level"), py::arg("msg"));

	m.def("alert", [](const char* msg) {
			  alert(msg);
	 }, "alert function",
		  py::arg("msg"));

	m.attr("WARNING_LEVEL") = py::cast(WARNING_LEVEL);

}
