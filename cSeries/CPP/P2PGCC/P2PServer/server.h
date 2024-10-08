// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file server.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/08/22 下午12:09
 * @brief
 * @copyright CC BY-NC-SA
 * */

#ifndef P2PCLIENT_SERVER_H
#define P2PCLIENT_SERVER_H
#pragma once

#include "../lib/proto.h"
#include "../lib/Exception.h"

namespace Glb {
    extern UserList clients;
}

void initWinsock();

class Server {
    private:
        std::shared_ptr<SOCKET> sock;
        sockaddr_in local;
        sockaddr_in remote;
        Msg::C2SMsg recvMsg;
    public:
        Server(const std::string& ip, unsigned short port, int type = SOCK_STREAM);
        std::shared_ptr<Msg::User> operator[](std::string name);
        [[noreturn]] void run();
};

#endif // P2PCLIENT_SERVER_H
