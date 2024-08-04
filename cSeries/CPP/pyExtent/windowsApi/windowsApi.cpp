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
 * @Date: 2024/07/03 下午5:52
 * @Commend: cpp extension for python
 *******************************************************/
#include <windows.h>
#include <psapi.h>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <tchar.h>
#include <cstdint>
#include "pybind11/pybind11.h"

namespace py = pybind11;


PYBIND11_MODULE(windowsApi, m) {
	m.doc() = "Windows API extension for Python";

	// function definitions
	m.def("OpenProcess", &OpenProcess, "Open a process by its ID and return its handle",
		  py::arg("dwDesiredAccess"), py::arg("bInheritHandle"), py::arg("dwProcessId"));
	m.def("CloseHandle", &CloseHandle, "Close a handle",
		  py::arg("hObject"));
	m.def("GetLastError", &GetLastError, "Get the last error code");
	m.def("EnumWindows", &EnumWindows, "Enumerate all the windows on the screen and call a callback function for each window",
		  py::arg("lpEnumFunc"), py::arg("lParam"));
	m.def("GetWindowThreadProcessId", &GetWindowThreadProcessId, "Get the process ID of a window",
		  py::arg("hWnd"), py::arg("lpdwProcessId"));
	m.def("GetWindowTextLength", &GetWindowTextLength, "Get the length of the text of a window",
		  py::arg("hWnd"));
	m.def("GetWindowText", &GetWindowText, "Get the text of a window",
		  py::arg("hWnd"), py::arg("lpString"), py::arg("nMaxCount"));
	m.def("GetWindowTextA", &GetWindowTextA, "Get the text of a window in ANSI encoding",
		  py::arg("hWnd"), py::arg("lpString"), py::arg("nMaxCount"));
	m.def("GetModuleBaseName", &GetModuleBaseName, "Get the base name of a module",
		  py::arg("hProcess"), py::arg("hModule"), py::arg("lpBaseName"), py::arg("nSize"));
	m.def("IsWindowVisible", &IsWindowVisible, "Check if a window is visible",
		  py::arg("hWnd"));
	m.def("IsWindowEnabled", &IsWindowEnabled, "Check if a window is enabled",
		  py::arg("hWnd"));
	m.def("EnumProcesses", &EnumProcesses, "Enumerate all the processes on the system and call a callback function for each process",
		  py::arg("lpidProcess"), py::arg("cb"), py::arg("lpcbNeeded"));
	m.def("FindWindow", &FindWindow, "Find a window by its class name and window name",
		  py::arg("lpClassName"), py::arg("lpWindowName"));

	// variable definitions
	m.attr("PROCESS_QUERY_INFORMATION") = py::cast(PROCESS_QUERY_INFORMATION);
	m.attr("PROCESS_VM_READ") = py::cast(PROCESS_VM_READ);
	m.attr("MAX_PATH") = py::cast(MAX_PATH);

}
