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
#include <iostream>

std::string User::toStr() const {
    return "[" + name + ": <" + addr.first + ":" + std::to_string(addr.second) + ">]";
}

bool User::operator==(const User &other) {
    return name == other.name && addr == other.addr;
}

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
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw SocketError("WSAStartup failed");
}

Socket::Socket(int family, int type) {
    sockfd = socket(family, type, 0);
    initWinsock();
    if (sockfd == INVALID_SOCKET) {
        WSACleanup();
        throw SocketError("create socket failed");
    }
}

Socket::~Socket() {
    closesocket(sockfd);
    WSACleanup();
}

void Socket::bind(const sockaddr_in &addr) const {
    if (::bind(sockfd, (SOCKADDR*)&addr, sizeof(addr)) < 0)
        throw SocketError("bind failed");
}

template<typename T>
void Socket::sendTo(const Msg<T> &msg, const std::string &ip, short port) {
    sendto(sockfd, )
}

template<typename T>
std::pair<Msg<T>, sockaddr_in> Socket::recvFrom(size_t bufSize) {
    char buf[bufSize];
    sockaddr_in addr{};
    int len = sizeof(addr);
    if (recvfrom(sockfd, buf, bufSize, 0, (SOCKADDR*)&addr, &len) < 0)
        throw SocketError("recvfrom failed");
    return std::make_pair(Msg<T>(buf), addr);
}

template<typename T>
T Socket::serialize(const Msg<T> &msg) {}
