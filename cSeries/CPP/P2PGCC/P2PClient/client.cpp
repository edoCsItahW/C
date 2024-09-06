// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: P2PClient
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/22 上午2:54
 * @Commend:
 *******************************************************/

#include "client.h"

int main(int argc, char* argv[]) {
    try {
        InitWinSock();

        Global::PrimaryUDP = mksock(SOCK_DGRAM);

        BindSock(Global::PrimaryUDP);

        std::cout << "Please input server ip:";
        std::cin >> Global::ServerIP;

        std::cout << "Please input your name:";
        std::cin >> Global::UserName;

        ConnectToServer(Global::PrimaryUDP, Global::UserName, Global::ServerIP);

        HANDLE threadhandle = CreateThread(nullptr, 0, RecvThreadProc, nullptr, 0, nullptr);

        CloseHandle(threadhandle);

        for (;;) {
            char input[COMMANDMAXC];
            ParseCommand(gets(input));
        }
    }
    catch (const Exception& e) { std::cerr << e.getMsg() << std::endl; }
    catch (const std::exception& e) { std::cerr << e.what() << std::endl; }
    return 0;
}
