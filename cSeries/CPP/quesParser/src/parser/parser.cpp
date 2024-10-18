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
 * @date 2024/10/10 下午10:12
 * @brief 题目解析器的语法分析器API实现
 * @copyright CC BY-NC-SA
 * */

#include "parser.h"

Parser::Parser(std::vector<Token> tokens)
    : _tokens(std::move(tokens))
    , _pos(0) {}

void Parser::consume(Parser::Type type, std::source_location loc) {
    if (_tokens[_pos].type == type)
        _pos++;
    else
        throw Exception("Expected token: " + tokenTypeNames[static_cast<int>(type)] + ", but got: " + tokenTypeNames[static_cast<int>(_tokens[_pos].type)] + " at " + std::to_string(_tokens[_pos].pos.first) + ":" + std::to_string(_tokens[_pos].pos.second), loc);
}

ast::Paper Parser::parse() {
    ast::Paper paper;
    while (_pos < _tokens.size() && _tokens[_pos].type != Type::END) paper.blocks.push_back(parseBlock());
    return paper;
}

ast::Block Parser::parseBlock() {
    ast::Block block{.question = parseQuestion()};
    while (_pos + 1 < _tokens.size() && _tokens[_pos].type == Type::NEWLINE && _tokens[_pos + 1].type == Type::LETTER) block.options.push_back(parseOption());
    return block;
}

std::optional<ast::Question> Parser::parseQuestion() {
    if (_tokens[_pos].type == Type::CONTENT) consume(Type::CONTENT);
    consume(Type::NEWLINE);
    if (_pos + 1 >= _tokens.size()) return std::nullopt;
    ast::Question ques{.index = _tokens[_pos]};
    consume(Type::INDEX);
    if (_tokens[_pos].type != Type::DOT)
        ques.dot = Token(Type::DOT, ques.index.pos + 1, ".");
    else {
        ques.dot = _tokens[_pos];
        consume(Type::DOT);
    }
    ques.content = parseContent();
    return ques;
}

ast::Option Parser::parseOption() {
    consume(Type::NEWLINE);
    ast::Option opt{.letter = _tokens[_pos]};
    consume(Type::LETTER);
    if (_tokens[_pos].type != Type::DOT)
        opt.dot = Token(Type::DOT, opt.letter.pos + 1, ".");
    else {
        opt.dot = _tokens[_pos];
        consume(Type::DOT);
    }
    opt.content = parseContent();
    return opt;
}

ast::Content Parser::parseContent() {
    ast::Content content;
    while (_tokens[_pos].type != Type::NEWLINE && _tokens[_pos].type != Type::END) {
        content.value += _tokens[_pos].value;
        _pos++;
    }
    return content;
}
