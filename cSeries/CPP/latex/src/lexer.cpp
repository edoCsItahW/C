// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file lexer.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/11/08 下午1:32
 * @brief
 * */
#include "lexer.h"

// ------------------------------ Token ----------------------------------

std::string Token::toString() const {
    return "Token[" + std::string(enumToStr(type)) + "]<" + std::to_string(pos.first) + ":" + std::to_string(pos.second) + ">('" + value + "')";
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token.toString();
    return os;
}

// ------------------------------ Lexer ---------------------------------

Lexer::Lexer(std::string text): _text(std::move(text)), _pos(0), _line(1), _col(1) {}
