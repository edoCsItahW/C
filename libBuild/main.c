// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: test
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/05/20 上午9:52
 * @Commend:
 *******************************************************/
#include <stdio.h>
#include <windows.h>

int main() {
	system("start cmd.exe"); // 弹出cmd窗口

	Sleep(1000); // 延时1秒

	while(1) {
		system("dir"); // 向cmd输入'dir'指令
		Sleep(500); // 每隔0.5秒执行一次
	}

	return 0;
}
//#include <windows.h>
//#include <stdio.h>
//
//int main() {
//	HANDLE hStdin, hStdout;
//	PROCESS_INFORMATION pi;
//	STARTUPINFO si;
//	DWORD dwWritten;
//
//	ZeroMemory(&si, sizeof(STARTUPINFO));
//	si.cb = sizeof(STARTUPINFO);
//	si.dwFlags = STARTF_USESTDHANDLES;
//
//	// 获取标准输入和输出句柄
//	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
//	hStdin = GetStdHandle(STD_INPUT_HANDLE);
//
//	// 创建子进程连接到cmd窗口
//	CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
//
//	// 向cmd窗口发送输入
//	WriteFile(hStdin, "dir\n", 4, &dwWritten, NULL);
//
//	// 关闭句柄
//	CloseHandle(pi.hProcess);
//	CloseHandle(pi.hThread);
//
//	return 0;
//}
