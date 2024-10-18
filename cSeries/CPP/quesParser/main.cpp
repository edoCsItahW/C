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
 * @date 2024/10/16 下午8:06
 * @brief 题目解析器测试程序
 * @copyright CC BY-NC-SA
 * */

#include "confunc.h"
#include "src/lexer/lexer.h"
#include "src/parser/parser.h"

int main() {
    auto content = os::readFile(R"(C:\Users\Lenovo\Desktop\test.txt)");
    
    Parser parser(Lexer::tokenize());
    for (auto& block : parser.parse().blocks)
        std::cout << block.question->index << std::endl;
    return 0;
}
