// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file _server.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/07 上午11:44
 * @brief
 * */

#ifndef P2PSERVER__SERVER_H
#define P2PSERVER__SERVER_H
#pragma once

// server.cpp
#include "../lib/_proto.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class Server {
    private:
        Socket sock;
        Clients clients;
        std::unordered_map<std::string, int> log;

    public:
        Server(uint16_t port)
            : sock() {
            sockaddr_in addr;
            memset(&addr, 0, sizeof(addr));
            addr.sin_family      = AF_INET;
            addr.sin_addr.s_addr = INADDR_ANY;
            addr.sin_port        = htons(port);
            sock.bind(addr);
            debug("Server started", addr);
        }

        User self() {
            return User("Server", sock.getsockname());
        }

        void keepAlive() {
            while (true) {
                for (const auto& client : clients) {
                    if (log[client.name] > 3) {
                        debug("Client " + client.name + " is offline, removing it", client.addr);
                        clients.removeUser(client);
                    } else {
                        Msg heartbeatMsg(ServerFlag::HEARTBEAT, self(), client);
                        sock.sendTo(heartbeatMsg, client.addr);
                        log[client.name]++;
                    }
                }
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
        }

        void listen() {
            std::thread(&Server::keepAlive, this).detach();
            while (true) {
                auto [data, addr] = sock.recvFrom();
                data.sender.addr  = addr;
                handle(data, addr);
            }
        }

        void handle(const Msg& data, const sockaddr_in& addr) {
            switch (data.flag) {
                case ServerFlag::LOGIN: {
                    debug("LOGIN " + data.sender.name, addr);
                    clients.addUser(data.sender);
                    sock.sendTo(Msg(ServerFlag::NONE, clients, data.sender), addr);
                    for (const auto& client : clients)
                        if (client != data.sender) sock.sendTo(Msg(ClientFlag::GETUSER, clients, client), client.addr);
                    break;
                }
                case ServerFlag::LOGOUT: {
                    debug("LOGOUT " + data.sender.name, addr);
                    clients.removeUser(data.sender);
                    break;
                }
                case ServerFlag::P2PTRANS: {
                    // Assuming data.info contains the target index or user info
                    if (int index = std::any_cast<int>(data.info); index >= 0 && index < clients.size()) {
                        User& user = clients[index];
                        debug("P2PTRANS " + data.sender.name + " -> " + user.name + " establish p2p communication request", addr);
                        sock.sendTo(Msg(ClientFlag::REQUEST, data.sender, user), user.addr);
                    } else {
                        sock.sendTo(Msg(ClientFlag::ERR, "User not found", data.sender), addr);
                    }
                    break;
                }
                case ServerFlag::GETUSER: {
                    debug("GETUSER " + data.sender.name + " get user list", addr);
                    sock.sendTo(Msg(ClientFlag::GETUSER, clients, data.sender), addr);
                    break;
                }
                case ServerFlag::HEARTBEAT: {
                    log[data.sender.name]--;
                    break;
                }
                case ServerFlag::ERR: {
                    debug("ERROR " + data.sender.name + " " + std::any_cast<std::string>(data.info), addr);
                    break;
                }
                default: std::cerr << "Unknown flag: " << static_cast<int>(data.flag) << std::endl; break;
            }
        }
};

int main() {
    try {
        Server server(5000);
        server.listen();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

#endif  // P2PSERVER__SERVER_H
