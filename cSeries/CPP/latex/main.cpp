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
 * @date 2024/11/08 下午1:33
 * @brief
 * */

#include "src/lexer.h"
#include <iostream>

int main() {
    std::cout << Token{TokenType::STRING, {1, 1}, "Hello, world!"} << std::endl;
}
