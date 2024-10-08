// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn


#include <iostream>
#include <string>
#include <list>
#include <cstring>
#include <stdexcept>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "../lib/_proto.h"
#include "../lib/_Exception.h"

#pragma comment(lib, "ws2_32.lib")

std::list<stUserListNode> ClientList;

void InitWinSock() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		throw std::runtime_error("Windows sockets 2.2 startup");
	} else {
		std::cout << "Using " << wsaData.szDescription << " (Status: " << wsaData.szSystemStatus << ")\n";
		std::cout << "with API versions " << LOBYTE(wsaData.wVersion) << "." << HIBYTE(wsaData.wVersion)
				  << " to " << LOBYTE(wsaData.wHighVersion) << "." << HIBYTE(wsaData.wHighVersion) << "\n\n";
	}
}

SOCKET mksock(int type) {
	SOCKET sock = socket(AF_INET, type, 0);
	if (sock < 0) {
		throw std::runtime_error("create socket error");
	}
	return sock;
}

stUserListNode GetUser(const std::string& username) {
	for (const auto& user : ClientList) {
		if (user.userName == username) {
			return user;
		}
	}
	throw std::runtime_error("not find this user");
}

// 192.168.56.1
int main(int argc, char* argv[]) {
	try {
		InitWinSock();

		SOCKET PrimaryUDP = mksock(SOCK_DGRAM);

		sockaddr_in local;
		local.sin_family = AF_INET;
		local.sin_port = htons(SERVER_PORT);
		local.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(PrimaryUDP, (sockaddr*)&local, sizeof(sockaddr)) == SOCKET_ERROR) {
			throw std::runtime_error("bind error");
		}

		sockaddr_in sender;
		stMessage recvbuf;
		memset(&recvbuf, 0, sizeof(stMessage));

		for (;;) {
			int dwSender = sizeof(sender);
			int ret = recvfrom(PrimaryUDP, (char*)&recvbuf, sizeof(stMessage), 0, (sockaddr*)&sender, &dwSender);
			if (ret <= 0) {
				std::cerr << "recv error\n";
				continue;
			} else {
				int messageType = recvbuf.iMsgType;
				switch (messageType) {
				case LOGIN: {
					std::cout << "has a user login: " << recvbuf.message.loginmember.userName << "\n";
					stUserListNode currentuser{};
					currentuser.userName = recvbuf.message.loginmember.userName;
					currentuser.ip = ntohl(sender.sin_addr.S_un.S_addr);
					currentuser.port = ntohs(sender.sin_port);

					ClientList.push_back(currentuser);

					int nodecount = static_cast<int>(ClientList.size());
					sendto(PrimaryUDP, (const char*)&nodecount, sizeof(int), 0, (const sockaddr*)&sender, sizeof(sender));
					for (const auto& user : ClientList) {
						sendto(PrimaryUDP, (const char*)&user, sizeof(stUserListNode), 0, (const sockaddr*)&sender, sizeof(sender));
					}
					break;
				}
				case LOGOUT: {
					std::cout << "has a user logout: " << recvbuf.message.logoutmember.userName << "\n";
					ClientList.remove_if([&](const stUserListNode& user) {
						return user.userName == recvbuf.message.logoutmember.userName;
					});
					break;
				}
				case P2PTRANS: {
					std::cout << inet_ntoa(sender.sin_addr) << " wants to p2p " << recvbuf.message.translatemessage.userName << "\n";
					stUserListNode node = GetUser(recvbuf.message.translatemessage.userName);
					sockaddr_in remote;
					remote.sin_family = AF_INET;
					remote.sin_port = htons(node.port);
					remote.sin_addr.s_addr = htonl(node.ip);

					in_addr tmp;
					tmp.S_un.S_addr = htonl(node.ip);
					std::cout << "the address is " << inet_ntoa(tmp) << ", and port is " << node.port << "\n";

					stP2PMessage transMessage;
					transMessage.iMsgType = P2PSOMEONEWANTTOCALLYOU;
					transMessage.iStringLen = ntohl(sender.sin_addr.S_un.S_addr);
					transMessage.Port = ntohs(sender.sin_port);

					sendto(PrimaryUDP, (const char*)&transMessage, sizeof(transMessage), 0, (const sockaddr*)&remote, sizeof(remote));
					break;
				}
				case GETALLUSER: {
					int command = GETALLUSER;
					sendto(PrimaryUDP, (const char*)&command, sizeof(int), 0, (const sockaddr*)&sender, sizeof(sender));

					int nodecount = static_cast<int>(ClientList.size());
					sendto(PrimaryUDP, (const char*)&nodecount, sizeof(int), 0, (const sockaddr*)&sender, sizeof(sender));

					for (const auto& user : ClientList) {
						sendto(PrimaryUDP, (const char*)&user, sizeof(stUserListNode), 0, (const sockaddr*)&sender, sizeof(sender));
					}
					break;
				}
				}
			}
		}
	} catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		return 1;
	}

	return 0;
}



