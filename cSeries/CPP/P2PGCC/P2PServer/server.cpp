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

namespace Glb {
    UserList clients{};
}

void initWinsock() {
    WSAData wsaData{};
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw Exception("Failed to initialize Winsock!");
    else
        std::cout << "使用`" << wsaData.szDescription << "`(状态: `" << wsaData.szSystemStatus << "`), API版本: '" << LOBYTE(wsaData.wVersion) << "." << HIBYTE(wsaData.wHighVersion) << "'至'"
                  << LOBYTE(wsaData.wHighVersion) << "." << HIBYTE(wsaData.wHighVersion) << "'.\n"
                  << std::endl;
}

Server::Server(const std::string& ip, unsigned short port, int type) {
    initWinsock();
    sock = std::make_shared<SOCKET>(socket(AF_INET, type, 0));
    if (sock == nullptr || *sock == INVALID_SOCKET) throw Exception("Failed to create socket!");
    local = sockaddr_in(AF_INET, htons(port));
//    local.sin_addr.s_addr = inet_addr(ip.c_str());
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(*sock, (sockaddr*)&local, sizeof(sockaddr)) == SOCKET_ERROR)
        throw Exception("Failed to bind socket!");
}

std::shared_ptr<Msg::User> Server::operator[](std::string name) {
    for (auto& user : Glb::clients)
        if (user->username == name)
            return user;
    throw  Exception("User not found!");
}

[[noreturn]] void Server::run() {
    while (true) {
        int len = sizeof(remote);
        if (recvfrom(*sock, (char*)&recvMsg, sizeof(Msg::C2SMsg), 0, (sockaddr*)&remote, &len) <= 0)
            continue;
        else {
            switch (recvMsg.type) {
                using enum MsgType;
                case LOGIN: {
                    std::cout << "用户 <" << recvMsg.msg.login->username << "> 登录!" << std::endl;
                    auto currUser = std::make_shared<Msg::User>(recvMsg.msg.login->username, ntohl(remote.sin_addr.S_un.S_addr), ntohs(remote.sin_port));
                    Glb::clients.push_back(currUser);
                    int count = static_cast<int>(Glb::clients.size());
                    sendto(*sock, (const char*)&count, sizeof(int), 0, (const sockaddr*)&remote, sizeof(remote));
                    for (auto& user : Glb::clients)
                        sendto(*sock, (const char*)user.get(), sizeof(Msg::User), 0, (const sockaddr*)&remote, sizeof(remote));
                    break;
                }
                case LOGOUT: {
                    std::cout << "用户 <" << recvMsg.msg.logout->username << "> 登出!" << std::endl;
                    for (int i = 0; i < Glb::clients.size(); i++)
                        if (Glb::clients[i]->username == recvMsg.msg.logout->username)
                            Glb::clients.erase(Glb::clients.begin() + i);
                    break;
                }
                case P2PTRANS: {
                    std::cout << "'" << inet_ntoa(remote.sin_addr) << "'向'" << recvMsg.msg.transMsg->username << "'发起点对点传输!" << std::endl;
                    auto user = (*this)[recvMsg.msg.transMsg->username];
                    sockaddr_in target{AF_INET, htons(user->port)};
                    target.sin_addr.s_addr = htonl(user->ip);
                    std::cout << "目标地址: " << inet_ntoa(target.sin_addr) << ":" << ntohs(target.sin_port) << std::endl;
                    auto transMsg = Msg::P2PMsg{TransType::REQUEST, static_cast<int>(ntohl(remote.sin_addr.S_un.S_addr)), ntohs(remote.sin_port)};
                    sendto(*sock, (const char*)&transMsg, sizeof(Msg::P2PMsg), 0, (const sockaddr*)&target, sizeof(target));
                    break;
                }
                case GETALLUSER: {
                    std::cout << "获取所有用户信息!" << std::endl;
                    sendto(*sock, (const char*)GETALLUSER, sizeof(MsgType), 0, (const sockaddr*)&remote, sizeof(remote));
                    int count = static_cast<int>(Glb::clients.size());
                    sendto(*sock, (const char*)&count, sizeof(int), 0, (const sockaddr*)&remote, sizeof(remote));
                    for (auto& user : Glb::clients)
                        sendto(*sock, (const char*)user.get(), sizeof(Msg::User), 0, (const sockaddr*)&remote, sizeof(remote));
                    break;
                }
            }
        }
    }
}
