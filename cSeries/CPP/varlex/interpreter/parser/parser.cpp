// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file parser.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/09/22 下午8:31
 * @brief
 * @copyright CC BY-NC-SA
 * */

/**
 * @page Parser 语法分析器
 *
 * @section 介绍
 *
 * @section VarLex的上下文无法文法(CFG)
 * @b 开始符: @c program
 * @b 终结符: @c NUM, @c STRING, @c
 * @b 非终结符: @c program
 * @b 产生式:
 * @code{.ebnf}
 * @endcode
 * */

#include "parser.h"

Parser::Parser(std::vector<std::unique_ptr<Token>> &tokens): tokens(tokens), pos(0) {}

void Parser::parse() {
    parseProgram();
    if (pos < tokens.size())
        throw std::runtime_error("Unexpected token: " + tokens[pos]->value);
}

inline void Parser::advance() {
    if (pos < tokens.size()) ++pos;
}

void Parser::expect(TokenType type, const std::string &value) {
    if (pos < tokens.size() &&
        tokens[pos]->type == type &&
        (value.empty() || tokens[pos]->value == value))
        advance();
    else
        throw std::runtime_error(std::format("Expected {}", TokenName[static_cast<int>(type)]));
}

std::unique_ptr<Token> Parser::peek() {
    if (pos < tokens.size()) return std::move(tokens[pos]);
    else return nullptr;
}

void Parser::parseProgram() {
    // 哪些token可以作为program的开始符号, 标识符, [, NUM, STRING
    while (peek() && peek()->type == TokenType::IDENTIFIER || peek()->type == TokenType::LBRACKET)
        parseSTMT();
}

void Parser::parseSTMT() {
    switch (peek()->type) {
        using enum TokenType;
        case IDENTIFIER:  // 标识符后跟=则为赋值语句,后跟[则为函数定义

        default:
            break;
    }
}
