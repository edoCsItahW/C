// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: C
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/06/27 下午9:20
 * @Commend:
 *******************************************************/
#include <thread>
#include <iostream>
#include <winsock2.h>


#pragma comment(lib, "libws2_32.lib")


class Client {
private:
	std::string _ip;
	int _port;

	static void sendLoop() {
		while (true) {

		}
	}

	static void recvLoop() {
		while (true) {

		}
	}

	static void startLoop() {
		std::thread sendThread(sendLoop);
		std::thread recvThread(recvLoop);

		sendThread.join();
		recvThread.join();

	}

public:
	explicit Client(std::string ip = "localhost", int port = 25565): _ip(std::move(ip)), _port(port) {}

	[[nodiscard]] std::string ip() const {return _ip;}

};


int main() {
	Client client;

	std::cout << client.ip() << std::endl;

}
