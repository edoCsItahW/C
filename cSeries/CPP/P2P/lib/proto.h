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
 * @date 2024/8/12 上午8:06
 * @brief P2P协议API头文件
 * @copyright CC BY-NC-SA
 * */

#ifndef C_PROTO_H
#define C_PROTO_H
#pragma once

#include <string>

#ifdef _WIN32
    #include "winsock2.h"
    #include "ws2tcpip.h"
#else
    #include "sys/socket.h"
    #include "netinet/in.h"
    #include "arpa/inet.h"
    #include "unistd.h"
#endif

/** @enum ServerFlag
 * @brief 服务端标志位枚举
 * @details 客户端与服务端通讯时行为标志位枚举
 * @warning 应保持协议一致
 * */
enum class ServerFlag {
    LOGIN = 1,  ///< 登录
    LOGOUT,  ///< 登出
    TRANS,  ///< 点对点通讯构建
    GETUSERS,  ///< 获取在线用户列表
    REDIRECT,  ///< 转发消息
    HEARTBEAT,  ///< 心跳包
    ERROR_,  ///< 错误信息
    NONE  ///< 无信息
};


/** @enum ClientFlag
 * @brief 客户端标志位枚举
 * @details 客户端与客户端通讯时行为标志位枚举
 * @warning 应保持协议一致
 * */
enum class ClientFlag {
    MSG = 101,  ///< 消息
    REQUEST,  ///< 穿孔请求
    RESPONSE,  ///< 穿孔响应
    TRASH,  ///< NAT穿透(垃圾信息)
    GETUSERS,  ///< 获取在线用户列表
    HEARTBEAT,  ///< 心跳包
    ERROR_,  ///< 错误信息
    NONE  ///< 无信息
};

/** @struct User
 * @brief 用户信息结构体
 * @details 用于存储用户信息
 * */
struct User {
    /** @var name
     * @public @memberof User
     * @brief 用户名
     * @details 客户端登录时发送的用户名
     * @invariant 自初始化后不应修改
     * @qualifier const
     * */
    const std::string name;
    /** @var addr
     * @public @memberof User
     * @brief 用户地址
     * @details 客户端登录时的网络地址
     * @qualifier const
     * @note 地址格式为(ip, port)
     * */
    const std::pair<std::string, short int> addr;
    /**
     * @public @memberof User
     * @brief 字符串化用户信息
     * @details 用于打印用户信息
     * @return 字符串化的用户信息
     * @todo 使用散列表管理用户信息
     * */
    [[nodiscard]] std::string toStr() const;
    /**
     * @public @memberof User
     * @brief 重载 == 运算符
     * @details 用于比较两个用户是否相同
     * @param other 另一个用户
     * @return 两个用户是否相同
     * */
    bool operator==(const User& other);
    /**
     * @brief 输出用户信息到流
     * @public @memberof User
     * */
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};


/** @struct Msg
 * @brief 消息结构体
 * @details 用于存储消息信息,并在端间传递
 * @tparam T 消息数据类型
 * */
template<typename T>
struct Msg {
    /** @var flag
     * @public @memberof Msg
     * @brief 消息标志位
     * @details 用于标识消息的类型
     * @invariant 自初始化后不应修改
     * @remark 初始值为 @ref ServerFlag::NONE
     * @see ServerFlag
     * */
    ServerFlag flag = ServerFlag::NONE;
    /** @var data
     * @public @memberof Msg
     * @brief 消息数据
     * @details 用于存储消息数据
     * @tparam T 消息数据类型
     * */
    T data;
    /** @var sender
     * @public @memberof Msg
     * @brief 消息发送者
     * @details 用于存储消息发送者信息
     * @see User
     * */
    User& sender;
    /** @var receiver
     * @public @memberof Msg
     * @brief 消息接收者
     * @details 用于存储消息接收者信息
     * @see User
     * */
    User& receiver;
};


void initWinsock();

class Socket {
private:
    /** @var sockfd
     * @private @memberof Socket
     * @brief 套接字描述符
     * @details 用于存储套接字描述符
     * @invariant 自初始化后不应修改
     * @note 仅在Windows平台使用
     * */
    SOCKET sockfd;

public:
    /**
     * @brief Socket 构造函数
     * @details 用于初始化套接字描述符
     * @param family 地址族
     * @param type 套接字类型
     * @remark 默认参数为IPv4 TCP流式套接字
     * */
    explicit Socket(int family = AF_INET, int type = SOCK_STREAM);
    /**
     * @brief Socket 析构函数
     * @details 用于释放套接字资源
     * */
    ~Socket();
    /**
     * @brief 绑定套接字到指定地址
     * @details 用于绑定套接字到指定地址
     * @param ip 目标地址
     * @param port 目标端口
     * */
    void bind(const sockaddr_in& addr) const;
    /**
     * @brief 发送数据到指定地址
     * @details 用于发送数据到指定地址
     * @param data 待发送数据
     * @param ip 目标地址
     * @param port 目标端口
     * @tparam T 消息数据类型
     * */
    template<typename T>
    void sendTo(const Msg<T>& msg, const std::string& ip, short int port);

    template<typename T>
    std::pair<Msg<T>, sockaddr_in> recvFrom(size_t bufSize = 1024);

    template<typename T>
    T serialize(const Msg<T>& msg);

    template<typename T>
    Msg<T> deserialize(const std::string& data);
};

#endif  // C_PROTO_H
