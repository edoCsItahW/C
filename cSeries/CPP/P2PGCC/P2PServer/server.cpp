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

#include "server.h"


int main() {
	try {
		InitWinSock();

		auto PrimaryUDP = mksock(SOCK_DGRAM);

		sockaddr_in local{};
		local.sin_family = AF_INET;
		local.sin_port = htons(SERVER_PORT);
		local.sin_addr.s_addr = htonl(INADDR_ANY);

		if (bind(PrimaryUDP, (sockaddr*)&local, sizeof(sockaddr)) == SOCKET_ERROR)
			throw Exception("bind failed");

		sockaddr_in sender{};
		Msg::Message recvbuf;
		memset(&recvbuf, 0, sizeof(Msg::Message));

		while (true) {
			int dwSender = sizeof(sender);
			int ret = recvfrom(PrimaryUDP, (char*)&recvbuf, sizeof(Msg::Message), 0, (sockaddr*)&sender, &dwSender);

			if (ret <= 0) {
				std::cerr << "recv failed\n" << std::endl;
				continue;
			}
			else {
				switch (recvbuf.iMsgType) {
					case MsgType::LOGIN: {
						std::cout << "has a user login: " << recvbuf.msg.logoutmember->username << "\n" << std::endl;
						Msg::UserListNode currentuser;
						currentuser.username = recvbuf.msg.logoutmember->username;
						currentuser.ip = ntohl(sender.sin_addr.S_un.S_addr);
						currentuser.port = ntohs(sender.sin_port);

						Global::ClientList.push_back(currentuser);

						int nodecount = static_cast<int>(Global::ClientList.size());

						sendto(PrimaryUDP, (const char*)&nodecount, sizeof(int), 0, (const sockaddr*)&sender, sizeof(sender));

						for (const auto& user : Global::ClientList)
							sendto(PrimaryUDP, (const char*)&user, sizeof(Msg::UserListNode), 0, (const sockaddr*)&sender, sizeof(sender));

						break;
					}
					case MsgType::LOGOUT: {
						std::cout << "has a user logout: " << recvbuf.msg.logoutmember->username << "\n";
						Global::ClientList.erase(std::remove_if(Global::ClientList.begin(), Global::ClientList.end(), [&](const Msg::UserListNode& user) { return user.username == recvbuf.msg.logoutmember->username; }));
						break;
					}
					case MsgType::P2PTRANS: {
						std::cout << inet_ntoa(sender.sin_addr) << " wants to p2p " << recvbuf.msg.translatemsg->username << "\n";
						auto node = GetUser(recvbuf.msg.translatemsg->username);

						sockaddr_in remote{};
						remote.sin_family = AF_INET;
						remote.sin_port = htons(node.port);
						remote.sin_addr.s_addr = htonl(node.ip);

						in_addr tmp{};
						tmp.S_un.S_addr = htonl(node.ip);

						std::cout << "the address is " << inet_ntoa(tmp) << ", and port is " << node.port << "\n" << std::endl;

						Msg::P2PMsg transMsg{};
						transMsg.iMsgType = P2PSOMEONEWANTTOCALLYOU;
						transMsg.iStrLen = ntohl(sender.sin_addr.S_un.S_addr);
						transMsg.port = ntohs(sender.sin_port);

						sendto(PrimaryUDP, (const char*)&transMsg, sizeof(transMsg), 0, (const sockaddr*)&remote, sizeof(remote));
						break;
					}
					case GETALLUSER: {
						int command = GETALLUSER;
						sendto(PrimaryUDP, (const char*)&command, sizeof(int), 0, (const sockaddr*)&sender, sizeof(sender));

						int nodecount = static_cast<int>(Global::ClientList.size());
						sendto(PrimaryUDP, (const char*)&nodecount, sizeof(int), 0, (const sockaddr*)&sender, sizeof(sender));

						for (const auto& user : Global::ClientList)
							sendto(PrimaryUDP, (const char*)&user, sizeof(Msg::UserListNode), 0, (const sockaddr*)&sender, sizeof(sender));
						break;
					}
				}
			}
		}
	}
	catch (const Exception& e) {
		std::cerr << e.getMsg() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
