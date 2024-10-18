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
 * @date 2024/08/22 上午2:54
 * @brief
 * @copyright CC BY-NC-SA
 * */

#ifndef P2PCLIENT_CLIENT_H
#define P2PCLIENT_CLIENT_H
#pragma once

#include "../lib/Exception.h"
#include "../lib/__proto.h"

/**
 * @namespace Glb
 * @brief 全局变量
 * @details 全局变量,存贮一些全局变量
 * */
namespace Glb {
    /**
     * @var recvACK
     * @brief 接收到ACK标志
     * @details 接收到ACK标志,用于判断是否接收到对方的ACK消息
     * @qualifier extern
     * */
    extern bool recvACK;
    /**
     * @var clientList
     * @brief 客户端列表
     * @details 客户端列表,用于存储客户端信息
     * @qualifier extern
     * */
    extern UserList clientList;
}

/**
 * @brief 初始化WinSock
 * @details 初始化WinSock,用于网络通信
 * @return void
 * */
void initWinSock();

/**
 * @class Client
 * @brief 客户端类
 * @details 客户端类,用于与服务器通信
 * */
class Client {
    private:
        /**
         * @var sock
         * @brief 套接字
         * @details 套接字,用于网络通信
         * @private @memberof Client
         * */
        std::shared_ptr<SOCKET> sock;
        /**
         * @var remote
         * @brief 远程地址
         * @details 远程地址,用于网络通信
         * @private @memberof Client
         * */
        sockaddr_in remote;
        /**
         * @var local
         * @brief 本地地址
         * @details 本地地址,用于网络通信
         * @private @memberof Client
         * */
        sockaddr_in local;
        /**
         * @var recvMsg
         * @brief 接收消息
         * @details 接收消息,用于与服务器通信
         * @private @memberof Client
         * */
        Msg::P2PMsg recvMsg;
    public:
        explicit Client(int type = SOCK_STREAM);
        /**
         * @brief 连接服务器
         * @details 连接服务器,用于与服务器通信
         * @param ip 服务器IP地址
         * @param name 客户端名称
         * @param port 服务器端口号
         * */
        void connect(const std::string& ip, const std::string& name, unsigned short port);
        /**
         * @brief 发送消息
         * @details 发送消息,用于与服务器通信
         * */
        void run();
        /**
         * @brief 接收消息
         * @details 接收消息,用于与服务器通信
         * */
        DWORD WINAPI handleRecv(LPVOID lpParam);
};


#endif // P2PCLIENT_CLIENT_H
