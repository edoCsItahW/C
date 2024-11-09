// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file test.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/10 下午4:43
 * @brief 测试调试器API功能
 * @copyright CC BY-NC-SA
 * */

#include "src/debuger.h"
#include <functional>

int test_commonFunc(int a, int b) {
    std::cout << "Common function called." << std::endl;
    throw std::runtime_error("Test exception");
    return a + b;
}

void test_voidFunc() {
    std::cout << "Void function called." << std::endl;
}

struct Test {
    int memberFunc(int a) {
        std::cout << "Member function called." << std::endl;
        throw std::runtime_error("Test exception");
        return a;
    }
    int refFunc(int a) {
        std::cout << "Reference function called." << std::endl;
        dbg::Debugger ref(&Test::memberFunc);
        ref(this, a);
        return a;
    }
};

/** @hiderefby */
int main() {
    using namespace dbg;

    Debugger commonFunc(test_commonFunc);
    commonFunc(1, 2);

    Test test;

    Debugger memberFunc(std::bind(&Test::memberFunc, &test, std::placeholders::_1));
    memberFunc(3);

    test.refFunc(4);

    return 0;
}
