// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file proto.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/20 上午8:06
 * @brief P2P协议API实现
 * @copyright CC BY-NC-SA
 * */

#include "proto.h"
#include "exception.h"
#include <algorithm>
#include <iostream>

std::string User::toStr() const {
    return "[" + name + ": <" + (std::holds_alternative<std::string>(addr.first) ? std::get<std::string>(addr.first) : std::to_string(std::get<u_long>(addr.first))) + ":" + std::to_string(addr.second)
        + ">]";
}

bool User::operator==(const User &other) const { return name == other.name && addr == other.addr; }

/**
 * @details 输出类似于`[Alice: <127.0.0.1:8080>]`的字符串
 * @param os 输出流
 * @param user 用户对象
 * @return 输出流
 * @see User
 * @related User
 * */
std::ostream &operator<<(std::ostream &os, const User &user) {
    os << user.toStr();
    return os;
}

void initWinsock() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) throw SocketError("WSAStartup failed");
}

sockaddr_in createAddr(ADDR_ARGS) {
    sockaddr_in addr{.sin_family = AF_INET};
    if (port >= 0) addr.sin_port = htons(port);
    if (std::holds_alternative<std::string>(ip))
        addr.sin_addr.s_addr = inet_addr(std::get<std::string>(std::move(ip)).c_str());
    else
        addr.sin_addr.s_addr = std::get<u_long>(ip);
    return addr;
}

Socket::Socket(int family, int type) {
    dbg::Debugger dbgInit(initWinsock);
    dbgInit();
    sockfd = socket(family, type, 0);
    if (sockfd == INVALID_SOCKET) {
        WSACleanup();
        throw SocketError("create socket failed");
    }
}

Socket::~Socket() {
    closesocket(sockfd);
    WSACleanup();
}

std::vector<std::string> split(const std::string &str, const char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter)) result.push_back(item);
    return result;
}

void Socket::bind(ADDR_ARGS) const {
    auto addr = createAddr(std::move(ip), port);
    if (::bind(sockfd, (SOCKADDR *)&addr, sizeof(addr)) < 0) throw SocketError("bind failed");
}

void Socket::bind(const Addr &addr) const {
    dbg::Debugger dbgBind([this](ADDR_ARGS) { bind(std::move(ip), port); });
    dbgBind(addr.first, addr.second);
}

void Socket::close() const {
    closesocket(sockfd);
    WSACleanup();
}

std::optional<User> Clients::operator[](const std::string &name) const {
    for (const auto &client : *this)
        if (client.name == name) return client;
    return std::nullopt;
}

void Clients::push_back(const User &user) {
    if (std::any_of(begin(), end(), [&user](const User &other) { return user == other; })) throw std::runtime_error("user already exists");
    std::vector<User>::push_back(user);
}

Clients &Clients::operator=(const Clients &other) {
    if (this != &other) std::vector<User>::operator=(other);
    return *this;
}

Clients &Clients::operator=(Clients &&other) noexcept {
    if (this != &other) std::vector<User>::operator=(std::move(other));
    return *this;
}

Clients &Clients::operator=(Clients *other) {
    if (this != other) std::vector<User>::operator=(*other);
    return *this;
}
