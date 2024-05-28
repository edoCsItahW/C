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
 * @Date: 2024/05/27 上午8:46
 * @Commend:
 *******************************************************/
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "libws2_32.lib")
#define BUFSIZE 4096

int main() {
	WSADATA wsaData;  // 包含有关 Windows 套接字实现的信息
	SOCKET ConnectSocket = INVALID_SOCKET;

	struct sockaddr_in server;

	// 初始化 Winsock
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	// 创建一个socket
	ConnectSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("socket failed: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// 设置服务器地址
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(9999);

	// 连接到服务器
	iResult = connect(ConnectSocket, (struct sockaddr *)&server, sizeof(server));
	if (iResult == SOCKET_ERROR) {
		printf("connect failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	int ExitFlag = 1;

	while (ExitFlag) {
		char* inp = (char*)malloc(1024*sizeof(char));

		printf("请输入要发送的数据: ");

		gets(inp);

		if (strcmp(inp, "exit") == 0) {
			ExitFlag = 0;
		}

		// 发送数据
		iResult = send(ConnectSocket, inp, (int)strlen(inp), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		char* recvbuf = (char*)malloc(BUFSIZE*sizeof(char));

		// 接收数据
		iResult = recv(ConnectSocket, recvbuf, BUFSIZE, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			printf("Data received: %s\n", recvbuf);
		} else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());

		free(recvbuf);

	}

	// 关闭socket
	closesocket(ConnectSocket);

	// 清理Winsock
	WSACleanup();

	return 0;
}