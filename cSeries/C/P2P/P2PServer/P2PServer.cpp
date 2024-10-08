// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/* P2P 程序服务端
 *
 * 文件名：P2PServer.c
 *
 * 日期：2004-5-21
 *
 * 作者：shootingstars(zhouhuis22@sina.com)
 *
 */
#pragma comment(lib, "ws2_32.lib")

#include "..\Exception.h"
#include "..\proto.h"
#include "windows.h"

UserList ClientList;

/**
 * @brief 初始化Windows Socket
 * @details 初始化一个socket,该socket用于后续的网络通信
 * WSADATA: Windows Sockets 数据结构,用于保存Windows Sockets的相关信息
 * WSAStartup: 启动Windows Sockets,初始化Winsock库,参数1指定版本号,参数2指向WSADATA结构
 * */
void InitWinSock() {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Windows sockets 2.2 startup");
        throw Exception("");
    } else {
        printf("Using %s (Status: %s)\n", wsaData.szDescription, wsaData.szSystemStatus);
        printf("with API versions %d.%d to %d.%d\n\n", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion), LOBYTE(wsaData.wHighVersion), HIBYTE(wsaData.wHighVersion));
    }
}

/**
 * @brief 创建一个socket
 * @details 根据指定的类型,创建一个socket
 * socket: 用于创建网络连接的通道,参数1指定协议族(AF_INET表示IPv4),参数2指定socket类型,参数3指定协议(0表示默认协议)
 * @param type 要创建的socket的类型,SOCK_DGRAM表示UDP,SOCK_STREAM表示TCP
 * @return 返回创建的socket的句柄
 * */
SOCKET mksock(int type) {
    SOCKET sock = socket(AF_INET, type, 0);
    if (sock < 0) {
        printf("create socket error");
        throw Exception("");
    }
    return sock;
}

/**
 * @brief 寻找(检查)是否有某个用户
 * @details 在用户列表中查找指定用户名的用户,如果找到,返回该用户的节点信息,否则抛出异常
 * @param username 要查找的用户名
 * @return 返回找到的用户的节点信息
 * */
stUserListNode GetUser(char *username) {
    for (UserList::iterator UserIterator = ClientList.begin(); UserIterator != ClientList.end(); ++UserIterator)
        if (strcmp(((*UserIterator)->userName), username) == 0) return *(*UserIterator);
    throw Exception("not find this user");
}

int main(int argc, char *argv[]) {
    try {
        InitWinSock();

        SOCKET PrimaryUDP;
        PrimaryUDP = mksock(SOCK_DGRAM);

        sockaddr_in local;  // sockaddr_in结构体用于保存本机地址信息
        local.sin_family      = AF_INET;
        local.sin_port        = htons(SERVER_PORT);
        local.sin_addr.s_addr = htonl(INADDR_ANY);
        int nResult           = bind(PrimaryUDP, (sockaddr *)&local, sizeof(sockaddr));
        if (nResult == SOCKET_ERROR) throw Exception("bind error");

        sockaddr_in sender;  // sender结构体用于保存发送方地址信息
        stMessage recvbuf;
        memset(&recvbuf, 0, sizeof(stMessage));  // memset函数用于将缓冲区清零

        // 开始主循环.
        // 主循环负责下面几件事情:
        // 一:读取客户端登陆和登出消息,记录客户列表
        // 二:转发客户p2p请求
        for (;;) {
            int dwSender = sizeof(sender);
            int ret      = recvfrom(PrimaryUDP, (char *)&recvbuf, sizeof(stMessage), 0, (sockaddr *)&sender, &dwSender);
            if (ret <= 0) {
                printf("recv error");
                continue;
            } else {
                int messageType = recvbuf.iMessageType;
                switch (messageType) {
                    case LOGIN: {
                        //  将这个用户的信息记录到用户列表中
                        printf("has a user login : %s\n", recvbuf.message.loginmember.userName);
                        stUserListNode *currentuser = new stUserListNode();
                        strcpy(currentuser->userName, recvbuf.message.loginmember.userName);
                        currentuser->ip   = ntohl(sender.sin_addr.S_un.S_addr);
                        currentuser->port = ntohs(sender.sin_port);

                        ClientList.push_back(currentuser);

                        // 发送已经登陆的客户信息
                        int nodecount = (int)ClientList.size();
                        sendto(PrimaryUDP, (const char *)&nodecount, sizeof(int), 0, (const sockaddr *)&sender, sizeof(sender));
                        for (UserList::iterator UserIterator = ClientList.begin(); UserIterator != ClientList.end(); ++UserIterator)
                            sendto(PrimaryUDP, (const char *)(*UserIterator), sizeof(stUserListNode), 0, (const sockaddr *)&sender, sizeof(sender));

                        break;
                    }
                    case LOGOUT: {
                        // 将此客户信息删除
                        printf("has a user logout : %s\n", recvbuf.message.logoutmember.userName);
                        UserList::iterator removeiterator = NULL;
                        for (UserList::iterator UserIterator = ClientList.begin(); UserIterator != ClientList.end(); ++UserIterator) {
                            if (strcmp(((*UserIterator)->userName), recvbuf.message.logoutmember.userName) == 0) {
                                removeiterator = UserIterator;
                                break;
                            }
                        }
                        if (removeiterator != NULL) ClientList.remove(*removeiterator);
                        break;
                    }
                    case P2PTRANS: {
                        // 某个客户希望服务端向另外一个客户发送一个打洞消息
                        printf("%s wants to p2p %s\n", inet_ntoa(sender.sin_addr), recvbuf.message.translatemessage.userName);
                        stUserListNode node = GetUser(recvbuf.message.translatemessage.userName);  // 查找目标客户
                        sockaddr_in remote;                                                        // 该remote是被请求方的地址信息
                        remote.sin_family      = AF_INET;
                        remote.sin_port        = htons(node.port);
                        remote.sin_addr.s_addr = htonl(node.ip);

                        in_addr tmp;
                        tmp.S_un.S_addr = htonl(node.ip);
                        printf("the address is %s,and port is %d\n", inet_ntoa(tmp), node.port);

                        stP2PMessage transMessage;
                        transMessage.iMessageType = P2PSOMEONEWANTTOCALLYOU;
                        transMessage.iStringLen   = ntohl(sender.sin_addr.S_un.S_addr);
                        transMessage.Port         = ntohs(sender.sin_port);

                        sendto(PrimaryUDP, (const char *)&transMessage, sizeof(transMessage), 0, (const sockaddr *)&remote, sizeof(remote));

                        break;
                    }

                    case GETALLUSER: {
                        int command = GETALLUSER;
                        sendto(PrimaryUDP, (const char *)&command, sizeof(int), 0, (const sockaddr *)&sender, sizeof(sender));

                        int nodecount = (int)ClientList.size();
                        sendto(PrimaryUDP, (const char *)&nodecount, sizeof(int), 0, (const sockaddr *)&sender, sizeof(sender));

                        for (UserList::iterator UserIterator = ClientList.begin(); UserIterator != ClientList.end(); ++UserIterator)
                            sendto(PrimaryUDP, (const char *)(*UserIterator), sizeof(stUserListNode), 0, (const sockaddr *)&sender, sizeof(sender));
                        break;
                    }
                }
            }
        }

    } catch (Exception &e) {
        printf(e.GetMessage());
        return 1;
    }

    return 0;
}
