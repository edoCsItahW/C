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
 * @Date: 2024/07/02 上午9:59
 * @Commend:
 *******************************************************/
#include "listeningKey.h"


void CtrlA(void) {
	printf("Ctrl+A pressed\n");
}


void CtrlShiftM(void) {
	printf("Ctrl+Shift+M pressed\n");
}


int main() {
	Shortcut* shortcuts1 = createShortcut(
		createShortcutKey(
			'A',
			enableModifierKeys(1, CTRL)
			), CtrlA);

	Shortcut* shortcuts2 = createShortcut(
		createShortcutKey(
			'M',
			enableModifierKeys(2, CTRL, SHIFT)
			), CtrlShiftM);

	ShortcutListGlobal.shortcuts = packShortcuts(2, shortcuts1, shortcuts2);
	ShortcutListGlobal.count = 2;

	listenKey(keyBoardHookProc);

	return 0;
}
