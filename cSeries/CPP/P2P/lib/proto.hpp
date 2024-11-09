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
 * @brief
 * @copyright CC BY-NC-SA
 * */

#ifndef C_PROTO_HPP
#define C_PROTO_HPP
#pragma once

#include "proto.h"
#include <cstring>
#include <format>

template<typename... Args>
char *serialize(Args &&...args) {
    size_t size = 0;
    (void)std::initializer_list<int>{(size += sizeof(args), 0)...};
    char *buf = new char[size];
    char *ptr = buf;
    (void)std::initializer_list<int>{(std::memcpy(ptr, &args, sizeof(args)), ptr += sizeof(args), 0)...};
    return buf;
}

template<typename T>
char *Msg<T>::serialize() const {
    return ::serialize(flag, sizeof(T), data, sender, receiver);
}

template<typename T>
Msg<T> Msg<T>::deserialize(const char *data) {
    Msg<T> msg;
    size_t orgTypeSize;
    std::memcpy(&msg.flag, data, sizeof(Flag));
    data += sizeof(Flag);
    std::memcpy(&orgTypeSize, data, sizeof(size_t));
    data += sizeof(size_t);
    std::memcpy(&msg.data, data, orgTypeSize);
    data += orgTypeSize;
    if (!std::is_same_v<T, void *>) msg.data = static_cast<T>(msg.data);
    std::memcpy(&msg.sender, data, sizeof(User));
    data += sizeof(User);
    std::memcpy(&msg.receiver, data, sizeof(User));
    return msg;
}

template<typename T>
void Socket::sendTo(const Msg<T> &msg, ADDR_ARGS) {
    dbg::Debugger dbgCreateAddr(createAddr);
    sockaddr_in addr = dbgCreateAddr(std::move(ip), port);
    char *msgBuf     = msg.serialize();
    if (sendto(sockfd, msgBuf, sizeof(msg.flag) + sizeof(size_t) + sizeof(T) + (2 * sizeof(User)), 0, (SOCKADDR *)&addr, sizeof(addr)) < 0)
        throw SocketError(std::format("<{}> -> {}:{}", strerror(errno), inet_ntoa(addr.sin_addr), ntohs(addr.sin_port)));
}

template<typename T>
void Socket::sendTo(const Msg<T> &msg, Addr addr) {
    dbg::Debugger dbgST(static_cast<void (Socket::*)(const Msg<T> &, ADDR_ARGS)>(&Socket::sendTo<T>));
    dbgST(this, msg, addr.first, addr.second);
}

template<typename T = void *>
std::pair<std::optional<Msg<T>>, std::optional<Addr>> Socket::recvFrom(int bufSize, bool wait) {
    auto anyAddr      = createAddr();
    socklen_t addrLen = sizeof(anyAddr);
    char buf[bufSize];
    while (recvfrom(sockfd, buf, bufSize, 0, (SOCKADDR *)&anyAddr, &addrLen) < 0)
        if (wait)
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        else
            return {std::nullopt, std::nullopt};
    auto msg = Msg<T>::deserialize(buf);
    return {
        msg, Addr{inet_ntoa(anyAddr.sin_addr), ntohs(anyAddr.sin_port)}
    };
}

#endif  // C_PROTO_HPP
