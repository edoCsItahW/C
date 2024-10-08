// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/* P2P ��������
 *
 * �ļ�����P2PServer.c
 *
 * ���ڣ�2004-5-21
 *
 * ���ߣ�shootingstars(zhouhuis22@sina.com)
 *
 */
#pragma comment(lib, "ws2_32.lib")

#include "..\Exception.h"
#include "..\proto.h"
#include "windows.h"

UserList ClientList;

/**
 * @brief ��ʼ��Windows Socket
 * @details ��ʼ��һ��socket,��socket���ں���������ͨ��
 * WSADATA: Windows Sockets ���ݽṹ,���ڱ���Windows Sockets�������Ϣ
 * WSAStartup: ����Windows Sockets,��ʼ��Winsock��,����1ָ���汾��,����2ָ��WSADATA�ṹ
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
 * @brief ����һ��socket
 * @details ����ָ��������,����һ��socket
 * socket: ���ڴ����������ӵ�ͨ��,����1ָ��Э����(AF_INET��ʾIPv4),����2ָ��socket����,����3ָ��Э��(0��ʾĬ��Э��)
 * @param type Ҫ������socket������,SOCK_DGRAM��ʾUDP,SOCK_STREAM��ʾTCP
 * @return ���ش�����socket�ľ��
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
 * @brief Ѱ��(���)�Ƿ���ĳ���û�
 * @details ���û��б��в���ָ���û������û�,����ҵ�,���ظ��û��Ľڵ���Ϣ,�����׳��쳣
 * @param username Ҫ���ҵ��û���
 * @return �����ҵ����û��Ľڵ���Ϣ
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

        sockaddr_in local;  // sockaddr_in�ṹ�����ڱ��汾����ַ��Ϣ
        local.sin_family      = AF_INET;
        local.sin_port        = htons(SERVER_PORT);
        local.sin_addr.s_addr = htonl(INADDR_ANY);
        int nResult           = bind(PrimaryUDP, (sockaddr *)&local, sizeof(sockaddr));
        if (nResult == SOCKET_ERROR) throw Exception("bind error");

        sockaddr_in sender;  // sender�ṹ�����ڱ��淢�ͷ���ַ��Ϣ
        stMessage recvbuf;
        memset(&recvbuf, 0, sizeof(stMessage));  // memset�������ڽ�����������

        // ��ʼ��ѭ��.
        // ��ѭ���������漸������:
        // һ:��ȡ�ͻ��˵�½�͵ǳ���Ϣ,��¼�ͻ��б�
        // ��:ת���ͻ�p2p����
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
                        //  ������û�����Ϣ��¼���û��б���
                        printf("has a user login : %s\n", recvbuf.message.loginmember.userName);
                        stUserListNode *currentuser = new stUserListNode();
                        strcpy(currentuser->userName, recvbuf.message.loginmember.userName);
                        currentuser->ip   = ntohl(sender.sin_addr.S_un.S_addr);
                        currentuser->port = ntohs(sender.sin_port);

                        ClientList.push_back(currentuser);

                        // �����Ѿ���½�Ŀͻ���Ϣ
                        int nodecount = (int)ClientList.size();
                        sendto(PrimaryUDP, (const char *)&nodecount, sizeof(int), 0, (const sockaddr *)&sender, sizeof(sender));
                        for (UserList::iterator UserIterator = ClientList.begin(); UserIterator != ClientList.end(); ++UserIterator)
                            sendto(PrimaryUDP, (const char *)(*UserIterator), sizeof(stUserListNode), 0, (const sockaddr *)&sender, sizeof(sender));

                        break;
                    }
                    case LOGOUT: {
                        // ���˿ͻ���Ϣɾ��
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
                        // ĳ���ͻ�ϣ�������������һ���ͻ�����һ������Ϣ
                        printf("%s wants to p2p %s\n", inet_ntoa(sender.sin_addr), recvbuf.message.translatemessage.userName);
                        stUserListNode node = GetUser(recvbuf.message.translatemessage.userName);  // ����Ŀ��ͻ�
                        sockaddr_in remote;                                                        // ��remote�Ǳ����󷽵ĵ�ַ��Ϣ
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
