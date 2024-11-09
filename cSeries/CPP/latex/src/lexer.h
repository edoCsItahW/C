// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file lexer.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/11/08 下午1:32
 * @brief
 * */
#ifndef CUBICEQ_LEXER_H
#define CUBICEQ_LEXER_H
#pragma once

#include <string>
#include <array>
#include <vector>

/**
 * @page Latex EBNF 上下文无关文法
 * @section Latex_EBNF
 * @code{.ebnf}
 * @endcode
 * */

template<auto Value>
constexpr auto enumToStr();

template<typename T, std::size_t N = 0>
constexpr auto enumMax();

template<typename T> requires std::is_enum_v<T>
constexpr auto enumToStr(T value);

enum class TokenType {
    UNKNOWN
};

struct Token {
    TokenType type;
    std::pair<size_t, size_t> pos;
    std::string value{};
    [[nodiscard]] std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

class Lexer {
private:
    using Type = TokenType;
    const std::string _text;
    size_t _pos;
    size_t _line;
    size_t _col;
    void skip();
    Token extract

public:
    explicit Lexer(std::string text);
    Token operator*();
    Lexer& operator++();
    Lexer operator++(int);
    Lexer& operator--();
    Lexer operator--(int);
    static std::vector<Token> tokenize(const std::string& text);
};

#include "lexer.hpp"

#endif  // CUBICEQ_LEXER_H
