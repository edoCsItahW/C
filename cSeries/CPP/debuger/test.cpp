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
    return a + b;
}

class Test {
public:
    int memberFunc(int a) {
        std::cout << "Member function called." << std::endl;
        return a;
    }
    static int staticFunc(int a) {
        std::cout << "Static function called." << std::endl;
        return a;
    }
    int privateRefFunc(int a) {
        std::cout << "Private ref function called." << std::endl;
        auto boundMethod = std::bind(&Test::privateFunc, this, std::placeholders::_1);
        boundMethod(a);
        return a;
    }

private:
    int privateFunc(int a) {
        std::cout << "Private function called." << std::endl;
        return a;
    }
};

/** @hiderefby */
int main() {
    using namespace debuger;

    Debuger decoratedFunction(test_commonFunc);
    decoratedFunction(1, 2);

    Test test;

    auto memberBoundMethod = std::bind(&Test::memberFunc, &test, std::placeholders::_1);
    memberBoundMethod(3);

    auto staticBoundMethod = std::bind(&Test::staticFunc, std::placeholders::_1);
    staticBoundMethod(4);

    return 0;
}
