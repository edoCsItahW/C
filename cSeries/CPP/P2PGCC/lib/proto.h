// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file proto.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/08/22 上午2:57
 * @brief 协议头文件
 * @copyright CC BY-NC-SA
 * */

#ifndef P2PCLIENT_PROTO_H
#define P2PCLIENT_PROTO_H
#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <windows.h>


/** 消息类型 */
enum class MsgType { LOGIN = 1, LOGOUT = 2, P2PTRANS = 3, GETALLUSER = 4 };

enum class TransType {
    MSG = 101,
    REQUEST = 102,
    RESPONSE = 103,
    TRASH = 104,
    GETUSER = 105
};

namespace Msg {
    /** 客户端登录时向服务器发送的消息 */
    struct Login {
        std::string username;
        std::string password;
    };

    /** 客户端注销时向服务器发送的消息 */
    struct Logout {
        std::string username;
    };

    /** Client向服务器请求另外一个Client(userName)向自己方向发送UDP打洞消息 */
    struct Translate {
        std::string username;
    };

    /** Client向服务器发送的消息格式 */
    struct C2SMsg {
        MsgType type;

        union _msg {
            std::shared_ptr<Login> login;
            std::shared_ptr<Logout> logout;
            std::shared_ptr<Translate> transMsg;

            _msg()
                : login(nullptr) {}

            ~_msg() {
                if (login) logout = nullptr;
                if (logout) transMsg = nullptr;
                if (transMsg) login = nullptr;
            }
        } msg;
    };

    /** 客户节点信息 */
    struct User {
        std::string username;
        unsigned int ip;
        unsigned short port;
    };

    /** Server向Client发送的消息 */
    struct S2CMsg {
        MsgType type;

        union _msg {
            User user;
        } msg;
    };

    /** 客户端之间发送消息格式 */
    struct P2PMsg {
        TransType type;
        int iStrLen;
        unsigned short port;
    };
}  // namespace Msg

using UserList = std::vector<std::shared_ptr<Msg::User>>;

#endif  // P2PCLIENT_PROTO_H
