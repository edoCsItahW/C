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
#include "test.h"
#include "confunc.h"
#include <iostream>

struct Visitor {
    void operator()(const std::string& str) {
        std::cout << str << std::endl;
    }
    void operator()(const std::wstring& wstr) {
        std::wcout << wstr << std::endl;
    }
};

int main() {
    using namespace os;
    AnyStr content = readFile(R"(C:\Users\Lenovo\Desktop\test.txt)", Type::GBK);
//    std::visit(Visitor(), content);
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::string>)
            std::cout << arg << std::endl;
        else if constexpr (std::is_same_v<T, std::wstring>)
            std::wcout << arg << std::endl;
    }, content);
    return 0;
}
