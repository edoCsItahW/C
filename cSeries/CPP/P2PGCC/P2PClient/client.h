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
 * @Date: 2024/08/22 上午2:54
 * @Commend:
 *******************************************************/

#ifndef P2PCLIENT_CLIENT_H
#define P2PCLIENT_CLIENT_H
#pragma once

#include "../lib/Exception.h"
#include "../lib/proto.h"

#define COMMANDMAXC 256
#define MAXRETRY 5

namespace Global {
	UserList ClientList;

	SOCKET PrimaryUDP;

	std::string UserName;

	std::string ServerIP;

	bool RecvedACK;
}


void InitWinSock() {
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Window sockets 2.2 startup" << std::endl;
		throw Exception("WSAStartup failed");
	}
	else {
		std::cout << "Using " << wsaData.szDescription << " (Status: " << wsaData.szSystemStatus << ")\n"
				  << "with API versions " << LOBYTE(wsaData.wVersion) << "." << HIBYTE(wsaData.wVersion)
				  << " to " << LOBYTE(wsaData.wHighVersion) << "." << HIBYTE(wsaData.wHighVersion) << std::endl;
	}
}

SOCKET mksock(int type) {
	SOCKET sock = socket(AF_INET, type, 0);

	if (sock == INVALID_SOCKET) {
		throw Exception("create socket failed");
	}
	return sock;
}

Msg::UserListNode GetUser(const std::string& username) {
	for (auto& user : Global::ClientList) {
		if (user.username == username)
			return user;
	}
	throw Exception("not find this user");
}

void BindSock(SOCKET sock) {
	sockaddr_in sin{};
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	sin.sin_family = AF_INET;
	sin.sin_port = 0;

	if (bind(sock, (sockaddr*)&sin, sizeof(sin)) < 0)
		throw Exception("bind error");
}

void ConnectToServer(SOCKET sock, const std::string& username, const std::string& serverip) {
	sockaddr_in remote{};
	remote.sin_addr.S_un.S_addr = inet_addr(serverip.c_str());
	remote.sin_family = AF_INET;
	remote.sin_port = htons(SERVER_PORT);

	Msg::Message sendBuf;

	sendto(sock, (const char*)&sendBuf, sizeof sendBuf, 0, (const sockaddr*)&remote, sizeof remote);

	int usercount;
	int fromlen = sizeof remote;
	int iread = recvfrom(sock, (char*)&usercount, sizeof(int), 0, (sockaddr*)&remote, &fromlen);

	if (iread <= 0) throw Exception("Login failed");

	std::cout << "Have " << usercount << " users logined server: " << std::endl;

	for (int i = 0; i < usercount; i++) {
		auto node = new Msg::UserListNode;

		recvfrom(sock, (char*)node, sizeof(Msg::UserListNode), 0, (sockaddr*)&remote, &fromlen);

		Global::ClientList.push_back(*node);

		std::cout << "Username:" << node->username << std::endl;
		in_addr tmp{};
		tmp.S_un.S_addr = htonl(node->ip);
		std::cout << "UserIP:" << inet_ntoa(tmp) << std::endl;
		std::cout << "UserPort:" << node->port << "\n" << std::endl;
	}
}

void OutputUsage() {
	std::cout << "You can input you command:\n"
			  << "Command Type: 'send', 'exit', 'getu'\n"
			  << "Example: send Username Message\n"
			  << "\texit\n"
			  << "\tgetu\n" << std::endl;
}

bool SendMsg(const std::string& username, const std::string& msg) {
	unsigned int UserIp;
	unsigned short UserPort;
	bool FindUser = false;

	for (auto& user : Global::ClientList)
		if (user.username == username) {
			UserIp = user.ip;
			UserPort = user.port;
			FindUser = true;
			break;
		}

	if (!FindUser) return false;

	for (int i = 0; i < MAXRETRY; i++) {
		Global::RecvedACK = false;

		sockaddr_in remote{};
		remote.sin_addr.S_un.S_addr = UserIp;
		remote.sin_family = AF_INET;
		remote.sin_port = htons(UserPort);

		Msg::P2PMsg MsgHead{};

		MsgHead.iMsgType = MsgType::P2PTRANS;
		MsgHead.iStrLen = static_cast<int>(msg.size()) + 1;

		int isend = sendto(Global::PrimaryUDP, (const char*)(&MsgHead), sizeof(MsgHead), 0, (const sockaddr*)&remote, sizeof(remote));
		isend = sendto(Global::PrimaryUDP, msg.c_str(), MsgHead.iStrLen, 0, (const sockaddr*)&remote, sizeof(remote));

		for (int j = 0; j < 10; j++)
			if (Global::RecvedACK)  return true;
			else Sleep(300);

		sockaddr_in server{};
		server.sin_addr.S_un.S_addr = inet_addr(Global::ServerIP.c_str());
		server.sin_family = AF_INET;
		server.sin_port = htons(SERVER_PORT);

		Msg::Message transMsg{};

		transMsg.iMsgType = MsgType::P2PTRANS;
		transMsg.msg.translatemsg->username = Global::UserName;

		sendto(Global::PrimaryUDP, (const char*)&transMsg, sizeof(transMsg), 0, (const sockaddr*)&server, sizeof(server));
		Sleep(100);
	}
	return false;
}

void ParseCommand(const std::string& cmd) {
	if (cmd.size() < 4) return;

	if (cmd == "exit") {
		Msg::Message sendBuf;
		sendBuf.iMsgType = MsgType::LOGOUT;
		sendBuf.msg.loginmember->username = Global::UserName;

		sockaddr_in server{};
		server.sin_addr.S_un.S_addr = inet_addr(Global::ServerIP.c_str());
		server.sin_family = AF_INET;
		server.sin_port = htons(SERVER_PORT);

		sendto(Global::PrimaryUDP, (const char*)&sendBuf, sizeof(sendBuf), 0, (const sockaddr*)&server, sizeof(server));

		Global::ClientList.clear();
		closesocket(Global::PrimaryUDP);
		WSACleanup();
		exit(0);
	}
	else if (cmd == "send") {
		std::string sendname;
		std::string msg;
		int i = 5;

		for (int i;; i++)
			if (cmd[i] != ' ') sendname[i - 5] = cmd[i];
			else {
				sendname[i - 5] = '\0';
				break;
			}
		msg = &cmd[i + 1];

		if (SendMsg(sendname, msg))
			std::cout << "Send message success" << std::endl;
		else
			std::cout << "Send message failed" << std::endl;
	}
	else if (cmd == "getu") {
		int command = GETALLUSER;
		sockaddr_in server{};
		server.sin_addr.S_un.S_addr = inet_addr(Global::ServerIP.c_str());
		server.sin_family = AF_INET;
		server.sin_port = htons(SERVER_PORT);

		sendto(Global::PrimaryUDP, (const char*)&command, sizeof(command), 0, (const sockaddr*)&server, sizeof(server));
	}
}

DWORD WINAPI RecvThreadProc(LPVOID lpParam) {
	sockaddr_in remote{};
	int sinlen = sizeof remote;
	Msg::P2PMsg recvBuf{};

	for (;;) {
		int iread = recvfrom(Global::PrimaryUDP, (char*)&recvBuf, sizeof(recvBuf), 0, (sockaddr*)&remote, &sinlen);

		if (iread <= 0) {
			std::cout << "Recv message failed" << std::endl;
			continue;
		}

		switch (recvBuf.iMsgType) {
			case P2PTRANS: {
				std::string msg = new char[recvBuf.iStrLen];
				int iread1 = recvfrom(Global::PrimaryUDP, (char*)msg.c_str(), recvBuf.iStrLen, 0, (sockaddr*)&remote, &sinlen);

				if (iread1 <= 0) throw Exception("Recv message failed");
				else {
					std::cout << "Recv message from " << inet_ntoa(remote.sin_addr) << ":" << ntohs(remote.sin_port) << " : " << msg << std::endl;

					Msg::P2PMsg sendBuf{};
					sendBuf.iMsgType = P2PMESSAGEACK;
					sendto(Global::PrimaryUDP, (const char*)&sendBuf, sizeof(sendBuf), 0, (const sockaddr*)&remote, sizeof(remote));

					break;
				}
			}
			case P2PSOMEONEWANTTOCALLYOU: {
				std::cout << "Recv p2someonewanttocallyou data\n" << std::endl;
				sockaddr_in remote{};
				remote.sin_addr.S_un.S_addr = htonl(recvBuf.iStrLen);
				remote.sin_family = AF_INET;
				remote.sin_port = htons(recvBuf.port);

				Msg::P2PMsg msg{};
				msg.iMsgType = P2PTRANS;

				sendto(Global::PrimaryUDP, (const char*)&msg, sizeof(msg), 0, (const sockaddr*)&remote, sizeof(remote));
				break;
			}
			case P2PMESSAGEACK: {
				Global::RecvedACK = true;
				break;
			}
			case P2PTRASH: {
				std::cout << "Recv p2ptrash data\n" << std::endl;
				break;
			}
			case GETALLUSER: {
				int usercount;
				int fromlen = sizeof remote;
				int iread = recvfrom(Global::PrimaryUDP, (char*)&usercount, sizeof(int), 0, (sockaddr*)&remote, &fromlen);

				if (iread <= 0) throw Exception("Get user failed");

				Global::ClientList.clear();

				std::cout << "Have " << usercount << " users logined server: " << std::endl;

				for (int i = 0; i < usercount; i++) {
					auto node = new Msg::UserListNode;

					recvfrom(Global::PrimaryUDP, (char*)node, sizeof(Msg::UserListNode), 0, (sockaddr*)&remote, &fromlen);

					Global::ClientList.push_back(*node);

					std::cout << "Username:" << node->username << std::endl;
					in_addr tmp{};
					tmp.S_un.S_addr = htonl(node->ip);
					std::cout << "UserIP:" << inet_ntoa(tmp) << std::endl;
					std::cout << "UserPort:" << node->port << "\n" << std::endl;
				}
				break;
			}
		}
	}
}

#endif // P2PCLIENT_CLIENT_H
