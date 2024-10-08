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
 * @date 2024/09/21 下午2:00
 * @brief
 * @copyright CC BY-NC-SA
 * */

#include "interpreter/parser/node.h"
//#include "interpreter/parser/parser.h"

int main() {
    auto text = readFile("../test/test.vl");

    auto tokens = Lexer::tokenize(text);

//    auto parser = Parser(tokens);
//
//    for (auto& node : parser.operator*())
//        std::cout << node->toString() << std::endl;

    return 0;
}
