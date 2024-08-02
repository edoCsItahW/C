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
 * @Date: 2024/07/10 下午5:44
 * @Commend:
 *******************************************************/
//#include "processRoundCheck.h"
#include "detectWindow.h"
#include <tlhelp32.h>
#include "../../../libBuild/array.h"


typedef struct {
	Process *process;
	PROCESS_MEMORY_COUNTERS pmc;
} ProcessPlus;


typedef struct {
	ProcessPlus** processPlus;
	int count;
} PPList;


void processMemory(DWORD pid, PPList* ppList) {
	HANDLE hProcess = getHandleByPid(pid);

	if (hProcess != NULL) {
		PROCESS_MEMORY_COUNTERS pmc;


		if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
//			printf("Process ID %lu: WorkingSetSize = %llu\n", pid, pmc.WorkingSetSize);

			ppList->count++;
			ppList->processPlus = realloc(ppList->processPlus, sizeof(ProcessPlus*) * ppList->count);
			ppList->processPlus[ppList->count - 1] = malloc(sizeof(ProcessPlus));
			ppList->processPlus[ppList->count - 1]->process = createProcess(pid);
			ppList->processPlus[ppList->count - 1]->pmc = pmc;
		}



		CloseHandle(hProcess);

	}
}

PPList* EnumerateProcessesByName(const char* processName) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapshot == INVALID_HANDLE_VALUE) {
		printf("CreateToolhelp32Snapshot failed (%lu)\n", GetLastError());
		return NULL;
	}

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hSnapshot, &pe32)) {
		printf("Process32First failed (%lu)\n", GetLastError());
		CloseHandle(hSnapshot);
		return NULL;
	}

	PPList* ppList = malloc(sizeof(PPList));
	ppList->processPlus = NULL;
	ppList->count = 0;

	do {
		char szProcessName[MAX_PATH] = "<unknown>";

		HANDLE hProcess = getHandleByPid(pe32.th32ProcessID);

		if (GetModuleBaseNameA(hProcess, NULL, szProcessName, sizeof(szProcessName))) {
			if (strcmp(szProcessName, processName) == 0) {
//				printf("Found process: %s (PID %lu)\n", szProcessName, pe32.th32ProcessID);

				processMemory(pe32.th32ProcessID, ppList);
			}
		}
	} while (Process32Next(hSnapshot, &pe32));

	CloseHandle(hSnapshot);

	return ppList;
}


int main() {
	WARNING_LEVEL = 4;

	const char* processName = "esbuild.exe";

	PPList* ppList = EnumerateProcessesByName(processName);

	int recordIdx;
	size_t recordSize;

	for (int i = 0; i < ppList->count; i++) {

		Process* p = ppList->processPlus[i]->process;
		PROCESS_MEMORY_COUNTERS ppm = ppList->processPlus[i]->pmc;

		printf("Process %s, PID: %lu, memory usage: %llu\n", p->processName, p->pid, ppm.WorkingSetSize);

		if (ppm.WorkingSetSize > recordSize) {
			recordSize = ppm.WorkingSetSize;
			recordIdx = i;
		}
	}


	for (int i = 0; i < ppList->count; i++) {

//		if (i != recordIdx) {
		WINBOOL result = TerminateProcess(ppList->processPlus[i]->process->handle, 0);

		printf("kill process %s, PID: %lu, result: %d\n", ppList->processPlus[i]->process->processName, ppList->processPlus[i]->process->pid, result);
//		}
	}

	free(ppList->processPlus);

	free(ppList);

	return 0;

}
