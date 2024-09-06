// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/* P2P ������Э��
 *
 * ���ڣ�2004-5-21
 *
 * ���ߣ�shootingstars(zhouhuis22@sina.com)
 *
 */

#pragma once
#include <list>

// ����iMessageType��ֵ
#define LOGIN		1
#define LOGOUT		2
#define P2PTRANS	3
#define GETALLUSER	4

// �������˿�
#define SERVER_PORT 2280

// Client��¼ʱ����������͵���Ϣ
struct stLoginMessage {
	char userName[10];
	char password[10];
};

// Clientע��ʱ���͵���Ϣ
struct stLogoutMessage {
	char userName[10];
};

// Client���������������һ��Client(userName)���Լ�������UDP����Ϣ
struct stP2PTranslate {
	char userName[10];
};

// Client����������͵���Ϣ��ʽ
struct stMessage {
	int iMsgType;
	union _message {
		stLoginMessage loginmember;
		stLogoutMessage logoutmember;
		stP2PTranslate translatemessage;
	} message;
};

// �ͻ��ڵ���Ϣ
struct stUserListNode {
	char* userName;
	unsigned int ip;
	unsigned short port;
};

// Server��Client���͵���Ϣ
struct stServerToClient {
	int iMsgType;
	union _message {
		stUserListNode user;
	} message;
};

//======================================
// �����Э�����ڿͻ���֮���ͨ��
//======================================
#define P2PMESSAGE	  100 // ������Ϣ
#define P2PMESSAGEACK 101 // �յ���Ϣ��Ӧ��
#define P2PSOMEONEWANTTOCALLYOU                                                                                        \
	102				 // ��������ͻ��˷��͵���Ϣ
					 // ϣ���˿ͻ��˷���һ��UDP�򶴰�
#define P2PTRASH 103 // �ͻ��˷��͵Ĵ򶴰������ն�Ӧ�ú��Դ���Ϣ

// �ͻ���֮�䷢����Ϣ��ʽ
struct stP2PMessage {
	int iMsgType;
	int iStringLen; // or IP address
	unsigned short Port;
};

using namespace std;
typedef list<stUserListNode *> UserList;
