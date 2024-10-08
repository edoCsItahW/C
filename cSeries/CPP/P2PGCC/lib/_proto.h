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
 * @date 2024/10/07 ÉÏÎç11:43
 * @brief
 * @copyright CC BY-NC-SA
 * */

#ifndef P2PSERVER__PROTO_H
#define P2PSERVER__PROTO_H
#pragma once

#include <any>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <unistd.h>
#endif

class User {
    public:
        std::string name;
        sockaddr_in addr;

        User(const std::string& name, const sockaddr_in& addr)
            : name(name)
            , addr(addr) {}

        std::string ip() const { return inet_ntoa(addr.sin_addr); }

        uint16_t port() const { return ntohs(addr.sin_port); }

        bool operator==(const User& other) const { return name == other.name && addr.sin_port == other.addr.sin_port && addr.sin_addr.s_addr == other.addr.sin_addr.s_addr; }

        friend std::ostream& operator<<(std::ostream& os, const User& user) {
            os << "[" << user.name << ": <" << user.ip() << ":" << user.port() << ">]";
            return os;
        }
};

enum class ServerFlag { LOGIN = 1, LOGOUT, P2PTRANS, GETUSER, NONE, REDIRECT, HEARTBEAT, ERR };

enum class ClientFlag { MSG = 101, REQUEST, RESPONSE, TRASH, GETUSER, HEARTBEAT, ERR };

class Msg {
    public:
        ServerFlag flag;
        std::any info;  // can be any data
        User sender;
        User receiver;

        Msg(ServerFlag flag, User sender, User receiver, std::any info = nullptr)
            : flag(flag)
            , sender(sender)
            , receiver(receiver)
            , info(info) {}
};

class Clients : public std::vector<User> {
    public:
        void addUser(const User& user) {
            if (std::find(this->begin(), this->end(), user) != this->end()) throw std::runtime_error("User already exists");
            this->push_back(user);
        }

        void removeUser(const User& user) { this->erase(std::remove(this->begin(), this->end(), user), this->end()); }
};

class Socket {
    private:
        int sockfd;
        sockaddr_in _addr;

    public:
        Socket(int family = AF_INET, int type = SOCK_DGRAM) {
            sockfd = socket(family, type, 0);
            if (sockfd < 0) throw std::runtime_error("Failed to create socket");
        }

        ~Socket() { closesocket(sockfd); }

        void bind(const sockaddr_in& addr) {
            _addr = addr;
            if (::bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) throw std::runtime_error("Failed to bind socket");
        }

        void sendTo(const Msg& msg, const sockaddr_in& addr) {
            std::string data = serialize(msg);  // Implement serialize method below
            sendto(sockfd, data.c_str(), data.size(), 0, (struct sockaddr*)&addr, sizeof(addr));
        }

        std::pair<Msg, sockaddr_in> recvFrom(size_t bufsize = 1024) {
            char buffer[bufsize];
            sockaddr_in addr;
            socklen_t addrlen = sizeof(addr);
            if (recvfrom(sockfd, buffer, bufsize, 0, (struct sockaddr*)&addr, &addrlen) < 0) throw std::runtime_error("Failed to receive data");
            Msg msg = deserialize(std::string(buffer, bufsize));  // Implement deserialize method below
            return {msg, addr};
        }

        sockaddr_in getsockname() const {
            return _addr;
        }

        std::string serialize(const Msg& msg);
        Msg deserialize(const std::string& data);
};

void debug(const std::string& msg, const sockaddr_in& addr) {
    std::cout << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << " [" << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << "] '" << msg << "'" << std::endl;
}

void debug(const std::string& msg, const char* ip, uint16_t port) {
    std::cout << ip << ":" << port << " [" << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << "] '" << msg << "'" << std::endl;
}

#endif  // P2PSERVER__PROTO_H
