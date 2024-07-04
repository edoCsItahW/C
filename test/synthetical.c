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
 * @Date: 2024/07/03 下午3:40
 * @Commend:
 *******************************************************/
#include "listeningKey.h"
#include "detectWindow.h"


void CtrlShiftM(void) {
	Process* process = getFoucsWindow();

	char className[256];

	printProcess(process);

	GetClassNameA(process->hwnd, className, sizeof className);

	printf("ClassName: %s\n", className);

	if (strcmp(className, "CabinetWClass") == 0) {
		HWND hPathContorl = NULL;
		hPathContorl = FindWindowEx(process->hwnd, NULL, "", NULL);

		if (hPathContorl != NULL) {
			char pathText[256];

			GetWindowTextA(hPathContorl, pathText, sizeof pathText);

			printf("Path: %s\n", pathText);

		}
		else
			warn(WARNING, "Can't find Breadcrumb Parent window");

	}

}


int main() {
//	WARNING_LEVEL = 4;
//
//	Shortcut* shortcut1 = createShortcut(
//		createShortcutKey(
//			'M',
//			enableModifierKeys(2, CTRL, SHIFT)
//			),
//		CtrlShiftM
//		);
//
//	ShortcutListGlobal.shortcuts = packShortcuts(1, shortcut1);
//	ShortcutListGlobal.count = 1;
//
//	listenKey(keyBoardHookProc);

	Process* process = findProcessByTitle("Python");

	char className[256];

	printProcess(process);

	GetClassNameA(process->hwnd, className, sizeof className);

	printf("ClassName: %s\n", className);

	if (strcmp(className, "CabinetWClass") == 0) {
		HWND hPathContorl = NULL;
		hPathContorl = FindWindowEx(process->hwnd, NULL, "", NULL);

		if (hPathContorl != NULL) {
			char pathText[256];

			GetWindowTextA(hPathContorl, pathText, sizeof pathText);

			printf("Path: %s\n", pathText);

		}
		else
			warn(WARNING, "Can't find Breadcrumb Parent window");

	}

}
