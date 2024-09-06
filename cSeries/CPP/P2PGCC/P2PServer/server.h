// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: P2PClient
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/22 下午12:09
 * @Commend:
 *******************************************************/

#ifndef P2PCLIENT_SERVER_H
#define P2PCLIENT_SERVER_H
#pragma once

#include "../lib/proto.h"
#include "../lib/Exception.h"

namespace Global {
	std::vector<Msg::UserListNode> ClientList;
}

void InitWinSock() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		throw Exception("Windows sockets 2.2 startup");
	else
		std::cout << "Using " << wsaData.szDescription << " (Status: " << wsaData.szSystemStatus << ")\n"
				  << "with API versions " << LOBYTE(wsaData.wVersion) << "." << HIBYTE(wsaData.wHighVersion)
				  << " to " << LOBYTE(wsaData.wHighVersion) << "." << HIBYTE(wsaData.wHighVersion) << "\n\n";
}

SOCKET mksock(int type) {
	SOCKET sock = socket(AF_INET, type, 0);

	if (sock < 0) throw Exception("create socket failed");

	return sock;
}

Msg::UserListNode GetUser(const std::string& username) {
	for (const auto& user : Global::ClientList)
		if (user.username == username)
			return user;
	throw Exception("not found user");
}

#endif // P2PCLIENT_SERVER_H
