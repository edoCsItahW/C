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
 * @date 2024/10/09 下午4:01
 * @brief
 * */

#include <chrono>
#include <json/json.h>
#include "proto.h"
#pragma comment(lib, "ws2_32.lib")

User::User(const std::string &name, const sockaddr_in &addr)
    : name(name)
    , addr(addr) {}

User::User(): name(""), addr{} {}

User::User(const User &other): name(other.name), addr(other.addr) {}

User::~User() = default;

std::string User::ip() const { return inet_ntoa(addr.sin_addr); }

uint16_t User::port() const { return ntohs(addr.sin_port); }

bool User::operator==(const User &other) const { return name == other.name && addr.sin_port == other.addr.sin_port && addr.sin_addr.s_addr == other.addr.sin_addr.s_addr; }

std::ostream &operator<<(std::ostream &os, const User &user) {
    os << "[" << user.name << ": <" << user.ip() << ":" << user.port() << ">]";
    return os;
}

Msg::Msg(ServerFlag flag, User sender, User receiver, std::any info)
    : flag(flag)
    , sender(sender)
    , receiver(receiver)
    , info(info) {}

Msg::Msg(const Msg &other): flag(other.flag), sender(other.sender), receiver(other.receiver), info(other.info) {}

Msg::~Msg() = default;

Socket::Socket(int family, int type)
    : sockfd(socket(family, type, 0)) {
    if (sockfd < 0) throw std::runtime_error("Failed to create socket");
}

Socket::~Socket() { closesocket(sockfd); }

void Socket::bind(const sockaddr_in &addr) {
    _addr = addr;
    if (::bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) throw std::runtime_error("Failed to bind socket");
}

void Socket::sendTo(const Msg &msg, const sockaddr_in &addr) {
    std::string data = serialize(msg);  // Implement serialize method below
    sendto(sockfd, data.c_str(), data.size(), 0, (struct sockaddr *)&addr, sizeof(addr));
}

std::pair<Msg, sockaddr_in> Socket::recvFrom(size_t bufsize) {
    auto buffer = new char[bufsize];
    sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    if (recvfrom(sockfd, buffer, bufsize, 0, (struct sockaddr *)&addr, &addrlen) < 0) {
        delete[] buffer;
        throw std::runtime_error("Failed to receive data");
    }
    Msg msg = deserialize(std::string(buffer, bufsize));  // Implement deserialize method below
    delete[] buffer;
    return {msg, addr};
}

sockaddr_in Socket::getsockname() const { return _addr; }

std::string Socket::serialize(const Msg &msg) {
    Json::Value j;
    j["flag"] = static_cast<int>(msg.flag);
    j["sender"] = msg.sender.name; // 需要扩展为 IP 和 port
    j["receiver"] = msg.receiver.name; // 同样需要扩展
    if (msg.info.has_value()) {
        j["info"] = std::any_cast<std::string>(msg.info);
    }
    return Json::writeString(Json::StreamWriterBuilder(), j);
}

Msg Socket::deserialize(const std::string &data) {
    Json::Value j;
    auto reader = Json::Reader();
    reader.parse(data, j);
    ServerFlag flag = static_cast<ServerFlag>(j["flag"].asInt());
    User sender(j["sender"].asString(), sockaddr_in{});
    User receiver(j["receiver"].asString(), sockaddr_in{});
    std::any info;

    if (j.isMember("info")) {
        info = j["info"].asString();
    }

    return {flag, sender, receiver, info};
}

void debug(const std::string &msg, const sockaddr_in &addr) {
    std::cout << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << " [" << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << "] '" << msg << "'" << std::endl;
}

void debug(const std::string &msg, const char *ip, uint16_t port) {
    std::cout << ip << ":" << port << " [" << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << "] '" << msg << "'" << std::endl;
}
