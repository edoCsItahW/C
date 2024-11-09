// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file client.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/20 下午7:15
 * @brief
 * */

#ifndef P2PSERVER_CLIENT_H
#define P2PSERVER_CLIENT_H
#pragma once

#include "../lib/proto.h"

class Client {
public:
    explicit Client(ADDR_ARGS_DECL, const char* name = nullptr);
    ~Client();
    User getSelf();
    [[nodiscard]] User getServer() const;
    void run();
private:
    const char* usage = "你可以输入以下命令: \n命令: send [name] [msg]  向指定用户发送消息 \n命令: getuser  获取在线用户列表 \n命令: exit  退出程序";
    Addr _addr;
    std::string _name;
    bool _ack;
    Socket _sock;
    User _self;
    User _server;
    Clients _clients;
    void login();
    void send(const std::string& name, const std::string& msg);
    void handle(Msg<void*>& msg, const Addr& addr);
    [[noreturn]] void listen();
};

#endif  // P2PSERVER_CLIENT_H
