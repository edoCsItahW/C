// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file _proto.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/07 上午11:43
 * @brief
 * @copyright CC BY-NC-SA
 * */

#ifndef P2PSERVER__PROTO_H
#define P2PSERVER__PROTO_H
#pragma once

#ifndef LIB
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

#include <vector>
#include <stdexcept>
#include <string>
#include <any>
#include <iostream>
#include <algorithm>
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <unistd.h>
#endif

class EXPORT User {
    public:
        std::string name;
        sockaddr_in addr;

        User(const std::string& name, const sockaddr_in& addr);
        User();
        ~User();
        User(const User& other);
        std::string ip() const;
        uint16_t port() const;
        bool operator==(const User& other) const;
        friend std::ostream& operator<<(std::ostream& os, const User& user);
};

enum class ServerFlag { LOGIN = 1, LOGOUT, P2PTRANS, GETUSER, NONE, REDIRECT, HEARTBEAT, ERR };

enum class ClientFlag { MSG = 101, REQUEST, RESPONSE, TRASH, GETUSER, HEARTBEAT, ERR };

class EXPORT Msg {
    public:
        ServerFlag flag;
        std::any info;  // can be any data
        User sender;
        User receiver;
        Msg(ServerFlag flag, User sender, User receiver, std::any info = nullptr);
        Msg(const Msg& other);
        ~Msg();
};

// 暂时将Clients及其实现注释掉皆可通过编译
class EXPORT Clients : public std::vector<User> {
    public:
        void push_back(const User &Val) {
            if (std::any_of(begin(), end(), [&Val](const User &user) { return user.name == Val.name; })) throw std::runtime_error("User already exists!");
            std::vector<User>::push_back(Val);
        }
        User& operator[](const std::string& name) {
            for (auto &client : *this) if (client.name == name) return client;
            throw std::runtime_error("User not found!");
        }
};

class EXPORT Socket {
    private:
        int sockfd;
        sockaddr_in _addr;

    public:
        Socket(int family = AF_INET, int type = SOCK_DGRAM);
        ~Socket();
        void bind(const sockaddr_in& addr);
        void sendTo(const Msg& msg, const sockaddr_in& addr);
        std::pair<Msg, sockaddr_in> recvFrom(size_t bufsize = 1024);
        sockaddr_in getsockname() const;
        std::string serialize(const Msg& msg);
        Msg deserialize(const std::string& data);
};

EXPORT void debug(const std::string& msg, const sockaddr_in& addr);

EXPORT void debug(const std::string& msg, const char* ip, uint16_t port);

#endif  // P2PSERVER__PROTO_H
