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
 * @Date: 2024/08/22 上午2:57
 * @Commend:
 *******************************************************/

#ifndef P2PCLIENT_PROTO_H
#define P2PCLIENT_PROTO_H
#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <windows.h>

#define SERVER_PORT 2280  // 服务器端口
#define P2PMESSAGE	  100 // 发送消息
#define P2PMESSAGEACK 101 // 收到消息的应答
#define P2PSOMEONEWANTTOCALLYOU 102
#define P2PTRASH 103

/** 消息类型 */
enum MsgType {
	LOGIN = 1,
	LOGOUT = 2,
	P2PTRANS = 3,
	GETALLUSER = 4
};

namespace Msg {
	/** 客户端登录时向服务器发送的消息 */
	struct LoginMsg {
		std::string username;
		std::string password;
	};

	/** 客户端注销时向服务器发送的消息 */
	struct LogoutMsg {
		std::string username;
	};

	/** Client向服务器请求另外一个Client(userName)向自己方向发送UDP打洞消息 */
	struct P2PTranslate {
		std::string username;
	};

	/** Client向服务器发送的消息格式 */
	struct Message {
		int iMsgType;
		union _msg {
			LoginMsg* loginmember;
			LogoutMsg* logoutmember;
			P2PTranslate* translatemsg;
			_msg() : loginmember(nullptr) {}
			~_msg() {
				if (loginmember) delete loginmember;
				if (logoutmember) delete logoutmember;
				if (translatemsg) delete translatemsg;
			}
		} msg;
	};

	/** 客户节点信息 */
	struct UserListNode {
		std::string username;
		unsigned int ip;
		unsigned short port;
	};

	/** Server向Client发送的消息 */
	struct ServerToClient {
		MsgType iMsgType;
		union _msg {
			UserListNode user;
		} msg;
	};

	/** 客户端之间发送消息格式 */
	struct P2PMsg {
		int iMsgType;
		int iStrLen;
		unsigned short port;
	};
}

using UserList = std::vector<Msg::UserListNode>;

#endif // P2PCLIENT_PROTO_H
