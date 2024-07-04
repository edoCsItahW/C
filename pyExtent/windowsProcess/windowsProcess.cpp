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
 * @Date: 2024/07/03 下午7:36
 * @Commend:
 *******************************************************/
#include "detectWindow.h"
#include "../pybind11/pybind11.h"


namespace py = pybind11;


using namespace std;


class ProcessWrapper {
public:
	explicit ProcessWrapper(DWORD pid) {
		process.pid = pid;
		process.hwnd = getHwndByPid(pid);
		process.handle = getHandleByPid(pid);
		process.processName = ::getProcessName(pid);
		process.windowTitle = ::getWindowTitle(pid);
	}

	[[nodiscard]] DWORD getPid() const {
		return process.pid;
	}

	[[nodiscard]] HWND getHwnd() const {
		return process.hwnd;
	}

	void setHwnd(HWND hwnd) {
		process.hwnd = hwnd;
	}

	[[nodiscard]] HANDLE getHandle() const {
		return process.handle;
	}

	void setHandle(HANDLE handle) {
		process.handle = handle;
	}

	[[nodiscard]] TCHAR* getProcessName() const {
		return process.processName;
	}

	void setProcessName(TCHAR* processName) {
		process.processName = processName;
	}

	[[nodiscard]] char* getWindowTitle() const {
		return process.windowTitle;
	}

	void setWindowTitle(char* windowTitle) {
		process.windowTitle = windowTitle;
	}

	~ProcessWrapper() {
		free(process.processName);
		free(process.windowTitle);
	}

private:
	Process process{};

};


class ProcessListWrapper {
public:
	ProcessListWrapper() {
		processList = [](ProcessList* plist) -> vector<ProcessWrapper> {
			vector<ProcessWrapper> pList;

			for (int i = 0; i < plist->count; i++) {
				pList.emplace_back(plist->processList[i]->pid);
				free(plist->processList[i]);
			}

			free(plist);

			return pList;

		}(getProcessListFromEnum());
	}

	explicit ProcessListWrapper(ProcessList* plist) {
		for (int i = 0; i < plist->count; i++) {
			processList.emplace_back(plist->processList[i]->pid);
			free(plist->processList[i]);
		}

		free(plist);
	}

	[[nodiscard]] vector<ProcessWrapper> getProcessList() const {
		return processList;
	}

	~ProcessListWrapper() {
		for (auto& item : getProcessList()) {
			free(item.getProcessName());
			free(item.getWindowTitle());
		}
	}

private:
	vector<ProcessWrapper> processList;

};


ProcessListWrapper getProcessListFromEnumWrapper() {
	return {};
}

ProcessListWrapper enumWindowsWrapper() {
	return ProcessListWrapper(enumWindows(NULL));
}


PYBIND11_MODULE(windowsProcess, m) {
	m.doc() = "A windows process api for python";

	py::class_<ProcessWrapper>(m, "Process")
	    .def(py::init<DWORD>())
		.def_property_readonly("pid", &ProcessWrapper::getPid)
		.def_property("hwnd", &ProcessWrapper::getHwnd, &ProcessWrapper::setHwnd)
		.def_property("handle", &ProcessWrapper::getHandle, &ProcessWrapper::setHandle)
		.def_property("processName", &ProcessWrapper::getProcessName, &ProcessWrapper::setProcessName)
		.def_property("windowTitle", &ProcessWrapper::getWindowTitle, &ProcessWrapper::setWindowTitle)
		.def("__repr__",
					   [](const ProcessWrapper& self) -> string {
						   return "windowsProcess.Process<pid: "
							   + to_string(self.getPid())
							   + ", processName: "
							   + self.getProcessName()
							   + ", windowTitle: "
							   + self.getWindowTitle()
							   + ", hwnd: "
							   + to_string((uintptr_t)self.getHwnd())
							   + ", handle: "
							   + to_string((uintptr_t)self.getHandle())
							   + ">";
					   });

	py::class_<ProcessListWrapper>(m, "ProcessList")
	    .def(py::init<>())
		.def_property_readonly("processList", [](ProcessListWrapper& self) -> py::list {
	       auto vec = self.getProcessList();

		   py::list result;

		   for (const auto& item : vec) result.append(item);

		   return result;

		});

	m.def("getHandleByPid", &getHandleByPid, "Get the handle of a process by its pid",
		  py::arg("pid"));
	m.def("getHwndByPid", &getHwndByPid, "Get the hwnd of a process by its pid",
		  py::arg("pid"));
	m.def("getPidByHandle", &getPidByHandle, "Get the pid of a process by its handle",
		  py::arg("handle"));
	m.def("getPidByHwnd", &getPidByHwnd, "Get the pid of a process by its hwnd",
		  py::arg("hwnd"));
	m.def("getProcessName", &getProcessName, "Get the process name of a process by its pid",
		  py::arg("pid"));
	m.def("getWindowTitleByHandle", &getWindowTitleByHandle, "Get the window title of a process by its handle",
		  py::arg("handle"));
	m.def("getWindowTitleByHwnd", &getWindowTitleByHwnd, "Get the window title of a process by its hwnd",
		  py::arg("hwnd"));
	m.def("getWindowTitle", &getWindowTitle, "Get the window title of a process by its pid",
		  py::arg("pid"));
	m.def("getProcessListFromEnum", &getProcessListFromEnumWrapper, "Get the list of all processes in the system");
	m.def("enumWindows", &enumWindowsWrapper, "Get the list of all windows in the system");
	m.def("findProcessByTitle", [](const char* title) -> ProcessWrapper {
			  Process* process = findProcessByTitle(title);

			  return ProcessWrapper(process->pid);

		  }, "Find the process by its window title",
		  py::arg("title"));
	m.def("getFoucsWindow", []() -> ProcessWrapper {
			  Process* process = getFoucsWindow();

			  return ProcessWrapper(process->pid);
	}, "Get the focused window");

}
