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

// 一个普通函数
void myFunction() {
    std::cout << "This is my function." << std::endl;
}

// 一个类
class MyClass {
    public:
        void myMethod() {
            std::cout << "This is my method." << std::endl;
        }
};

int main() {
    using namespace debuger;
    // 使用装饰器包装普通函数
    Debuger decoratedFunction(myFunction);
    decoratedFunction(); // 调用装饰后的函数

    // 使用装饰器包装类方法
    MyClass myClass;

    // 使用 std::bind 绑定类方法和对象
    auto decoratedMethod = Debuger(std::bind(&MyClass::myMethod, &myClass));
    decoratedMethod(); // 调用装饰后的方法

    return 0;
}
