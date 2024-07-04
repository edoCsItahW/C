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
 * @Date: 2024/07/03 上午10:58
 * @Commend:
 *******************************************************/
#include <windows.h>
#include <psapi.h>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <tchar.h>
#include <cstdint>
#include "warning.h"


typedef struct {
	DWORD pid;
	TCHAR* processName;
	HANDLE handle;
	HWND hwnd;
	char* windowTitle;
} Process;


typedef struct {
	Process** processList;
	int count;
} ProcessList;


typedef struct {
	DWORD pid;
	HWND hwnd;
} _TempStorage;


void destroyProcessList(ProcessList* processList) {
	free(processList->processList);
	free(processList);
}


HANDLE getHandleByPid(DWORD pid) {
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

	if (hProcess != NULL) return hProcess;
	else {
		warn(INFO, "OpenProcess failed (%lu)\n", GetLastError());
		return NULL;
	}
}


DWORD getPidByHwnd(HWND hwnd);


BOOL CALLBACK _ewProc(HWND hwnd, LPARAM lParam) {
	DWORD lpdwPid = getPidByHwnd(hwnd);
	_TempStorage* tmp = (_TempStorage*)lParam;

	if (lpdwPid == tmp->pid) {
		tmp->hwnd = hwnd;
		return FALSE;
	}
	return TRUE;
}


HWND getHwndByPid(DWORD pid) {
	_TempStorage tmp;
	tmp.pid = pid;
	tmp.hwnd = NULL;

	EnumWindows(_ewProc, (LPARAM)&tmp);

	if (tmp.hwnd == NULL)
		warn(WARNING, "Failed to get hwnd for process %lu\n", pid);

	return tmp.hwnd;
}


DWORD getPidByHandle(HANDLE handle) {
	DWORD pid = GetProcessId(handle);

	if (pid == 0) {
		warn(WARNING, "GetProcessId by handle failed (%lu)\n", GetLastError());
		return 0;
	}

	return pid;
}


DWORD getPidByHwnd(HWND hwnd) {
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);

	if (pid == 0) {
		warn(WARNING, "GetProcessId by hwnd failed (%lu)\n", GetLastError());
		return 0;
	}

	return pid;
}


TCHAR* getProcessName(DWORD pid) {
	HANDLE hProcess = getHandleByPid(pid);
	TCHAR* processName = (TCHAR*)calloc(MAX_PATH, sizeof(TCHAR));

	if (hProcess) {
		GetModuleBaseName(hProcess, NULL, processName, MAX_PATH);

		CloseHandle(hProcess);
	}

	return processName;

}


char* getWTbyAutoLen(HWND hwnd) {
	int len = GetWindowTextLength(hwnd);

	if (len > 0) {
		char* title = (char*)calloc(len + 1, sizeof(char));

		if (title != NULL) GetWindowTextA(hwnd, title, len + 1);
		else
			warn(INFO, "Memory allocation failed in getWTbyAutoLen\n");

		return title;
	}
	else {
		warn(WARNING, "Failed to get window title for window %p\n", hwnd);
		return NULL;
	}

}


char* getWindowTitleByHandle(HANDLE handle) {
	HWND hwnd = (HWND)handle;

	char* title = getWTbyAutoLen(hwnd);

	return title;
}


char* getWindowTitleByHwnd(HWND hwnd) {
	char* title = getWTbyAutoLen(hwnd);

	return title;
}


char* getWindowTitle(DWORD pid) {
	HANDLE handle = getHandleByPid(pid);

	char* title = getWindowTitleByHandle(handle);

	if (title != NULL && strlen(title) != 0) return title;

	HWND hwnd = getHwndByPid(pid);

	title = getWindowTitleByHwnd(hwnd);

	if (title != NULL && strlen(title) != 0) return title;
	else {
		warn(WARNING, "Failed to get window title for process %lu\n", pid);
		free(title);
		return NULL;
	}

}


void fillProcessPart(Process* process, DWORD pid) {
	process->pid = pid;
	process->processName = getProcessName(pid);
}


void fillWindowPart(Process* process, DWORD pid) {
	process->hwnd = getHwndByPid(pid);
	process->handle = getHandleByPid(pid);
	process->windowTitle = getWindowTitle(pid);
}


void fillProcess(Process* process, DWORD pid) {
	fillProcessPart(process, pid);
	fillWindowPart(process, pid);
}


Process* createProcess(DWORD pid) {
	Process* process = (Process*)calloc(1, sizeof(Process));

	fillProcess(process, pid);

	return process;
}


ProcessList* getProcessListFromEnum() {
	DWORD processIds[1024], cbNeeded, count;
	unsigned int i;
	Process** processSet;

	if (!EnumProcesses(processIds, sizeof(processIds), &cbNeeded))
		return NULL;

	count = cbNeeded / sizeof(DWORD);

	processSet = (Process**)calloc(count, sizeof(Process*));

	for (i = 0; i < count; i++) {
		if (processIds[i] != 0) processSet[i] = createProcess(processIds[i]);
	}

	ProcessList* processList = (ProcessList*)calloc(1, sizeof(ProcessList));

	processList->processList = processSet;
	processList->count = (int)count;

	return processList;

}


void printProcess(Process* process) {
	printf("Process: {\n"
		   "\tPID: %lx\n"
		   "\tprocessName: %s\n"
		   "\thwnd: %llu\n"
		   "\thandle: %llu\n"
		   "\twindowTitle: %s\n"
		   "}\n", process->pid, process->processName, (uintptr_t)process->hwnd, (uintptr_t)process->handle, process->windowTitle);
}


void printProcessList(ProcessList* processList) {
	for (int i = 0; i < processList->count; i++) {
		printProcess(processList->processList[i]);
	}
	destroyProcessList(processList);
}


BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam) {
	ProcessList* processList = (ProcessList*)lParam;

	DWORD pid = getPidByHwnd(hwnd);

	if (pid == 0) {
		warn(WARNING, "Failed to get process id for window %p\n", hwnd);
	}

	processList->processList[processList->count] = createProcess(pid);
	processList->count++;

	return TRUE;

}


ProcessList* enumWindows(ProcessList* processList) {
	if (processList == NULL) processList = (ProcessList*)malloc(sizeof(ProcessList));

	EnumWindows(enumWindowsProc, (LPARAM)processList);

	return processList;
}


Process* findProcessByTitle(const char* title) {
	HWND hwnd = FindWindow(NULL, title);

	if (hwnd == NULL) {
		warn(WARNING, "Failed to find window with title %s\n", title);
		return NULL;
	}

	return createProcess(getPidByHwnd(hwnd));
}


Process* getFoucsWindow() {
	HWND hwnd = GetForegroundWindow();

	DWORD pid = getPidByHwnd(hwnd);

	if (pid == 0) {
		warn(WARNING, "Failed to get process id for window %p\n", hwnd);
		return NULL;
	}

	Process* process = createProcess(pid);

	return process;

}
