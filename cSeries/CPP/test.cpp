// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file test.cpp
 * @author edocsitahw
 * @version 1.0.0
 * @date 2024/08/15 上午9:20
 * @brief 测试文件
 * @copyright CC BY-NC-SA
 * */
#include <iostream>


template<typename F>
class Debugger {
public:
    explicit Debugger(F func): _func(std::move(func)) {}

    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(auto) {
        return _func(std::forward<Args>(args)...);
    }
private:
    F _func;
};

template<class C, typename F>
class Debugger<F C::*> {
public:
    explicit Debugger(F C::*func): _func(func) {}

    template<typename... Args>
    auto operator()(C* obj, Args&&... args) -> decltype(auto) {
        return (obj->*_func)(std::forward<Args>(args)...);
    }

private:
    F C::*_func;
};


struct Test {
    int member(int a, int b) {
        std::cout << "member func run, res is: " << (a + b) << std::endl;
        return a + b;
    }
};


int func(int a, int b) {
    std::cout << "common func run, res is: " << (a + b) << std::endl;
    return a + b;
}


int main() {
    Debugger dbgFunc(func);
    dbgFunc(1, 2);

    Test test;
    Debugger dbgMember(&Test::member);
    dbgMember(&test, 1, 2);
    return 0;
}
