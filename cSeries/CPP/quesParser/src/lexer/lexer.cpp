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
 * @date 2024/10/10 下午9:59
 * @brief 题目解析器的词法分析器API实现
 * @copyright CC BY-NC-SA
 * */

#include "lexer.h"

std::string Token::toString() const {
    return "Token<" + std::to_string(pos.first) + ":" + std::to_string(pos.second) + ">(" + tokenTypeNames[static_cast<int>(type)] + ", \"" + value + "\")";
}

/**
 * @brief 重载输出流运算符
 * @details 重载输出流运算符,用于打印Token结构体.打印类似"Token<pos>(type, value)"
 * @param os 输出流
 * @param token 要输出的Token结构体
 * @return 输出流
 * @public @memberof Token
 * @see Token
 * @related Token
 * */
std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token.toString();
    return os;
}

Lexer::Lexer(std::string text)
    : _text(std::move(text))
    , _pos(0)
    , _line(1)
    , _col(1) {}

Token Lexer::operator*() {
    skip();
    if (_pos >= _text.size()) return {type::END, {_line, _col}};

    char c = _text[_pos];
    if (c == '\n') {
        _pos++;
        return {type::NEWLINE, {_line++, _col = 1}, "\\n"};
    } else if (c == '.' || c == L'、') {
        _pos++;
        return {type::DOT, {_line, _col++}, "."};
    } else if (isdigit(c))
        return extractIndex();
    else if (isalpha(c) && (c >= 'A' && c <= 'D'))
        return extractLetter();
    else
        return extractContent();
}

Lexer& Lexer::operator++() {
    ++_pos;
    return *this;
}

Lexer Lexer::operator++(int) {
    Lexer tmp(*this);
    ++_pos;
    return tmp;
}

Lexer& Lexer::operator--() {
    --_pos;
    return *this;
}

Lexer Lexer::operator--(int) {
    Lexer tmp(*this);
    --_pos;
    return tmp;
}

void Lexer::skip() {
    while (_pos < _text.size() && isspace(_text[_pos]) && _text[_pos] != '\n') {
        _pos++;
        _col++;
    }
}

Token Lexer::extractIndex() {
    std::string index;
    std::pair<size_t, size_t> start = {_line, _col};
    while (_pos < _text.size() && isdigit(_text[_pos])) {
        index += _text[_pos++];
        _col++;
    }
    return {type::INDEX, start, index};
}

Token Lexer::extractLetter() { return {type::LETTER, {_line, _col++}, std::string(1, _text[_pos++])}; }

Token Lexer::extractContent() {
    std::string content;
    std::pair<size_t, size_t> start = {_line, _col};
    while (_pos < _text.size() && _text[_pos] != '\n') {
        content += _text[_pos++];
        _col++;
    }
    return {type::CONTENT, start, content};
}

std::vector<Token> Lexer::tokenize(const std::string& text) {
    std::vector<Token> tokens;
    Lexer lexer(text);
    Token token;

    while ((token = *lexer).type != TokenType::END) tokens.push_back(std::move(token));
    return tokens;
}
