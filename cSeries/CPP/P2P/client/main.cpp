// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file main.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/20 下午8:56
 * @brief
 * @copyright CC BY-NC-SA
 * */

#include "client.h"
#pragma comment(lib, "ws2_32.lib")

int main() {
    Client client("127.0.0.1", 5000, "pc");
    client.run();
    return 0;
}
