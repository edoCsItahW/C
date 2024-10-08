// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file client.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/08/22 ����2:54
 * @brief
 * */

#include "client.h"

namespace Glb {
    bool recvACK = false;
    UserList clientList{};
}

void initWinSock() {
    WSAData wsaData{};
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw Exception("Failed to initialize Winsock!");
    else
        std::cout << "ʹ��`" << wsaData.szDescription << "`(״̬: `" << wsaData.szSystemStatus << "`), API�汾: '" << LOBYTE(wsaData.wVersion) << "." << HIBYTE(wsaData.wHighVersion) << "'��'"
                  << LOBYTE(wsaData.wHighVersion) << "." << HIBYTE(wsaData.wHighVersion) << "'.\n"
                  << std::endl;
}

Client::Client(int type) {
    initWinSock();
    sock = std::make_shared<SOCKET>(socket(AF_INET, type, 0));
    if (sock == nullptr || *sock == INVALID_SOCKET) throw Exception("Failed to create socket!");
    local = sockaddr_in{AF_INET, 0};
    local.sin_addr.s_addr = INADDR_ANY;
    if (bind(*sock, (struct sockaddr*)&local, sizeof(local)) < 0) throw Exception("Failed to bind socket!");
}

void Client::connect(const std::string& name, const std::string& ip, unsigned short port) {
    remote = sockaddr_in{AF_INET, htons(port)};
    remote.sin_addr.s_addr = inet_addr(ip.c_str());
    Msg::C2SMsg sendMsg{.type = MsgType::LOGIN};
    sendMsg.msg.login = std::make_shared<Msg::Login>(Msg::Login{.username = name});
    sendto(*sock, (const char*)&sendMsg, sizeof(sendMsg), 0, (const sockaddr*)&remote, sizeof(remote));
    int recvlen = sizeof(remote), count;
    if (recvfrom(*sock, (char*)&count, sizeof(int), 0, (sockaddr*)&remote, &recvlen) == SOCKET_ERROR)
        throw Exception("Login failed!");
    std::cout << "����" << count << "���û�." << std::endl;
    for (int i = 0; i < count; i++) {
        auto user = std::make_shared<Msg::User>();
        recvfrom(*sock, (char*)&user, sizeof(Msg::User), 0, (sockaddr*)&remote, &recvlen);
        Glb::clientList.push_back(user);
        std::cout << "�û�<" << user->username << ">����������." << std::endl;
    }
}

void Client::run() {
    std::string ip, name;
    unsigned short port;
    std::cout << "�����������IP��ַ:";
    std::cin >> ip;
    std::cout << "������������˿ں�:";
    std::cin >> port;
    std::cout << "�������û���:";
    std::cin >> name;
    connect(name, ip, port);

    auto recvThread = CreateThread(nullptr, 0, [](LPVOID lpParam) -> DWORD {
        static_cast<Client*>(lpParam)->handleRecv(lpParam);
        return 0;
    }, this, 0, nullptr);
    CloseHandle(recvThread);
    std::cout << "�����б�: send, exit, getu." << std::endl;
    while (true) {
        std::string cmd;
        std::cout << "����������: ";
        std::cin >> cmd;
        std::cout << cmd << std::endl;
        if (cmd == "exit") break;
    }
}

DWORD WINAPI Client::handleRecv(LPVOID lpParam) {
    while (true) {
        int len = sizeof(remote);
        if (recvfrom(*sock, (char*)&recvMsg, sizeof(recvMsg), 0, (sockaddr*)&remote, &len) <= 0) {
            std::cout << "Failed to receive data!" << std::endl;
            continue;
        }
        switch (recvMsg.type) {
            using enum TransType;
            case MSG: {
                char* msg = new char[recvMsg.iStrLen];
                if (recvfrom(*sock, (char*)&msg, sizeof(msg), 0, (sockaddr*)&remote, &len) <= 0)
                    throw Exception("Failed to receive data!");
                else {
                    std::cout << "�յ�����<" << inet_ntoa(remote.sin_addr) << ">����Ϣ: '" << msg << "'" << std::endl;
                    Msg::P2PMsg sendMsg{.type = RESPONSE};
                    sendto(*sock, (const char*)&sendMsg, sizeof(sendMsg), 0, (sockaddr*)&remote, len);
                }
                delete[] msg;
                break;
            }
            case REQUEST: {
                std::cout << "�յ�����<" << inet_ntoa(remote.sin_addr) << ">��ͨѶ����." << std::endl;
                remote.sin_addr.s_addr = htonl(recvMsg.iStrLen);
                remote.sin_family = AF_INET;
                remote.sin_port = htons(recvMsg.port);
                Msg::P2PMsg sendMsg{.type = TRASH};
                sendto(*sock, (const char*)&sendMsg, sizeof(sendMsg), 0, (sockaddr*)&remote, len);
                break;
            }
            case RESPONSE: {
                Glb::recvACK = true;
                break;
            }
            case TRASH: {
                break;
            }
            case GETUSER: {
                int recvlen = sizeof(remote), count;
                if (recvfrom(*sock, (char*)&count, sizeof(int), 0, (sockaddr*)&remote, &recvlen) <= 0)
                    throw Exception("Failed to receive data!");
                Glb::clientList.clear();
                std::cout << "����" << count << "���û�." << std::endl;
                for (int i = 0; i < count; i++) {
                    auto user = std::make_shared<Msg::User>();
                    recvfrom(*sock, (char*)&user, sizeof(Msg::User), 0, (sockaddr*)&remote, &recvlen);
                    Glb::clientList.push_back(user);
                    std::cout << "�û�<" << user->username << ">����������." << std::endl;
                }
                break;
            }
        }
    }
}
