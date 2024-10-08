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
 * @Date: 2024/07/03 下午2:04
 * @Commend:
 *******************************************************/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


typedef enum {
	SHIFT=0,
	CTRL,
	ALT,
	CAPSLOCK,
	TAB,
	ENTER,
	ESC,
	SPACE,
	BACKSPACE,
	RIGHT_CTRL,
	RIGHT_ALT,
	RIGHT_SHIFT,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	NUMDEL,
	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,
	NUMADD,
	NUMSUB,
	NUMMUL,
	NUMDIV,
} ModifierKey;


int KeyMap[] = {
	VK_SHIFT,
	VK_CONTROL,
	VK_MENU,
	VK_CAPITAL,
	VK_TAB,
	VK_RETURN,
	VK_ESCAPE,
	VK_SPACE,
	VK_BACK,
	VK_RCONTROL,
	VK_RMENU,
	VK_RSHIFT,
	VK_UP,
	VK_DOWN,
	VK_RIGHT,
	VK_LEFT,
	VK_DELETE,
	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,
	VK_ADD,
	VK_SUBTRACT,
	VK_MULTIPLY,
	VK_DIVIDE
};


typedef struct {
	int* keys;
	int count;
} KeyList;


typedef struct {
	WORD vkCode;
	KeyList* keyList;
} ShortcutKey;


typedef struct {
	ShortcutKey* shortcutKey;
	void (*func)(void);
} Shortcut;


typedef struct {
	Shortcut** shortcuts;
	int count;
} ShortcutList;


BOOL intToBool(int value) {
	return value ? TRUE : FALSE;
}


KeyList* enableModifierKeys(int count, ...) {
	va_list args;
	va_start(args, count);

	KeyList* keyList = (KeyList*)malloc(sizeof(KeyList));

	keyList->keys = (int*)malloc(count * sizeof(int));
	keyList->count = count;

	for (int i = 0; i < count; i++) {

		int key = (int)va_arg(args, ModifierKey);

		keyList->keys[i] = KeyMap[key];

	}

	return keyList;

}


ShortcutKey* createShortcutKey(WORD vkCoke, KeyList* keyList) {
	ShortcutKey* shortcutKey = (ShortcutKey*)malloc(sizeof(ShortcutKey));

	shortcutKey->vkCode = vkCoke;
	shortcutKey->keyList = keyList;

	return shortcutKey;
}


Shortcut* createShortcut(ShortcutKey* shortcutKey, void (*func)(void)) {

	Shortcut* shortcut = (Shortcut*)malloc(sizeof(Shortcut));

	shortcut->shortcutKey = shortcutKey;
	shortcut->func = func;

	return shortcut;
}


Shortcut** packShortcuts(int count, ...) {
	va_list args;
	va_start(args, count);

	Shortcut** shortcuts = (Shortcut**)malloc(sizeof(Shortcut*) * count);

	for (int i = 0; i < count; i++) {
		shortcuts[i] = va_arg(args, Shortcut*);
	}

	return shortcuts;
}


ShortcutList ShortcutListGlobal = {NULL, 0};


BOOL checkKeys(ShortcutKey* shortcutKey, KBDLLHOOKSTRUCT* kbHook) {
	BOOL keySignal = TRUE;

	for (int i = 0; i < shortcutKey->keyList->count; i++) {
		if (intToBool(GetAsyncKeyState(shortcutKey->keyList->keys[i]) & 0x8000)) {
			if (keySignal != FALSE) keySignal = TRUE;
		}
		else keySignal = FALSE;
	}

	if (kbHook->vkCode == shortcutKey->vkCode && keySignal) return TRUE;
	else return FALSE;
}


LRESULT CALLBACK keyBoardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
			KBDLLHOOKSTRUCT* kbHook = (KBDLLHOOKSTRUCT*)lParam;

			for (int i = 0; i < ShortcutListGlobal.count; i++) {
				if (checkKeys(ShortcutListGlobal.shortcuts[i]->shortcutKey, kbHook)) {
					ShortcutListGlobal.shortcuts[i]->func();
				}
			}

		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}


void listenKey(HOOKPROC lpfn) {
	HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, lpfn, NULL, 0);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(hHook);
}

