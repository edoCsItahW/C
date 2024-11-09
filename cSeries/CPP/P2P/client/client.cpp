// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file client.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/20 下午7:15
 * @brief
 * */

#include "client.h"
#include <thread>

Client::Client(ADDR_ARGS, const char *name)
    : _addr(std::holds_alternative<std::string>(ip) ? std::move(ip) : ip, port)
    , _name(name)
    , _sock(AF_INET, SOCK_STREAM)
    , _ack(false) {}

Client::~Client() = default;

User Client::getSelf() {
    if (_self.name != _name) _self.name = _name;
    return _self;
}

User Client::getServer() const { return _server; }

void Client::login() {
    if (_name.empty()) std::cin >> _name;
    _sock.sendTo(Msg{.flag = ServerFlag::LOGIN, .sender = getSelf(), .receiver = getServer()});
    auto [data, tmp] = _sock.recvFrom();
    _clients         = reinterpret_cast<Clients*>(std::move(data.value().data));
}

[[noreturn]] void Client::listen() {
    while (true) {
        auto [data, addr] = _sock.recvFrom<void *>(1024, false);
        if (data.has_value()) {
            data.value().sender.addr = addr.value();
            handle(data.value(), addr.value());
        } else
            continue;
    }
}

void Client::handle(Msg<void *> &msg, const Addr &addr) {
    if (std::holds_alternative<ClientFlag>(msg.flag)) switch (std::get<ClientFlag>(msg.flag)) {
            using enum ClientFlag;
            case MSG: {
                std::cout << "接受到信息: " << static_cast<const char *>(msg.data) << std::endl;
                _sock.sendTo(Msg{.flag = RESPONSE, .sender = getSelf(), .receiver = msg.sender}, addr);
                break;
            }
            case REQUEST: {
                _sock.sendTo(Msg{.flag = TRASH, .sender = getSelf(), .receiver = msg.sender}, static_cast<User *>(msg.data)->addr);
                break;
            }
            case RESPONSE: _ack = true; break;
            case TRASH: break; /** 不做任何事情 */
            case HEARTBEAT: {
                _sock.sendTo(Msg{.flag = HEARTBEAT, .sender = getSelf(), .receiver = msg.sender}, _addr);
                break;
            }
            case GETUSERS: {
                _clients = static_cast<Clients *>(msg.data);
                break;
            }
            case ERROR_: throw SocketError(static_cast<const char *>(msg.data));
            default: std::cerr << "Invalid flag" << std::endl;
        }
    else
        throw std::runtime_error("Invalid flag");
}

void Client::run() {
    try {
        login();
        std::thread thread(&Client::listen, this);
        thread.detach();
        std::cout << usage << std::endl;
        std::string cmd;
        while (std::cin >> cmd, !cmd.empty()) {
            auto cmds = split(cmd, ' ');
            if (cmds[0] == "exit") {
                _sock.sendTo(Msg{.flag = ServerFlag::LOGOUT, .sender = getSelf(), .receiver = getServer()}, _addr);
                _sock.close();
                break;
            } else if (cmds[0] == "getuser")
                _sock.sendTo(Msg{.flag = ServerFlag::GETUSERS, .sender = getSelf(), .receiver = getServer()}, _addr);
            else if (cmds[0] == "send") {
                std::stringstream ss;
                for (int i = 2; i < cmds.size(); i++) ss << cmds[i] << " ";
                send(cmds[1], ss.str());
            }
        }
    } catch (const SocketError &e) {
        std::cerr << e.what() << std::endl;
        _sock.sendTo(Msg{.flag = ServerFlag::ERROR_, .data = e.what(), .sender = getSelf(), .receiver = getServer()}, _addr);
    } catch (const std::exception &e) {
        _sock.sendTo(Msg{.flag = ServerFlag::LOGOUT, .sender = getSelf(), .receiver = getServer()}, _addr);
        _sock.close();
        std::terminate();
    }
}

void Client::send(const std::string &name, const std::string &msg) {
    auto receiver = _clients[name];
    if (receiver.has_value()) {
        _ack = false;
        _sock.sendTo(Msg{.flag = ClientFlag::MSG, .data = msg.c_str(), .sender = getSelf(), .receiver = receiver.value()});
        for (int i = 0; i < 3; i++)
            if (_ack) break;
            else
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
        _sock.sendTo(Msg{.flag = ServerFlag::TRANS, .sender = getSelf(), .receiver = getServer()}, _addr);
    } else
        std::cerr << "Error: " << name << " not found" << std::endl;
}
