// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file parser.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/09/22 下午8:31
 * @brief
 * @copyright CC BY-NC-SA
 * */

/**
 * @defgroup ebnf EBNF语法
 * @brief 程序的EBNF语法
 * @code{.ebnf}
 * <program> ::= { <statement> | <functionDefinition> | <classDefinition> }  ; 程序由语句、函数定义、类定义组成
 * <statement> ::= <assignment> | <output> | <controlFlowStatement>  ; 语句可以是赋值、输出、控制流语句
 * <assignment> ::= <identifier> "=" <expression> ";"  ; 赋值语句
 * <output> ::= <stringLiteral> "->;"  ; 输出语句
 * <controlFlowStatement> ::= <ifStatement> | <forLoop> | <whileLoop>  ; 控制流语句可以是if语句、for循环、while循环
 * <ifStatement> ::= "[" <expression> "," <block> { "-" "[" <expression> "," <block> ] } [ "-" <block> ] "]"  ; if语句，可以有多个分支，最后一个分支可以没有条件
 * <forLoop> ::= "[" <iterable> "," <identifier> { "," <identifier> } "=>" <block> "]"  ; 简化的for循环，未完全遵循标准
 * <whileLoop> ::= "[" <expression> "," <block> "]"  ; while循环
 * <functionDefinition> ::= "function" <identifier> "(" [ <parameterList> [ "|" <defaultParameterList> ] ] ")" "->" <type> "{" <block> "}"  ; 函数定义
 * <parameterList> ::= <identifier> { "," <identifier> }  ; 函数参数列表
 * <defaultParameterList> ::= <identifier> ":" <expression> { "," <identifier> ":" <expression> }  ; 默认参数列表
 * <classDefinition> ::= "class" <identifier> "(" [ <baseClass> ] ")" "[" <memberVariableDeclarations> "]" "{" { <functionDefinition> } "}"  ; 类定义
 * <baseClass> ::= <identifier>  ; 基类
 * <memberVariableDeclarations> ::= <identifier> ":" <type> { "," <identifier> ":" <type> }  ; 成员变量声明
 * <block> ::= "{" { <statement> } "}"  ; 代码块
 * <expression> ::= <term> { ("+" | "-") <term> }  ; 表达式由一系列的项组成
 * <term> ::= <factor> { ("*" | "/") <factor> }   ; 项由一系列的因子组成
 * <factor> ::= <identifier> | <numberLiteral> | <stringLiteral> | "(" <expression> ")"  ; 因子可以是标识符、数字、字符串、表达式
 * <identifier> ::= <letter> { <letter> | <digit> }  ; 标识符由字母和数字组成
 * <numberLiteral> ::= <digit> { <digit> }  ; 数字字面值
 * <stringLiteral> ::= '"' { <character> - '"' } '"'  ; 字符串字面值
 * <character> ::= <anyPrintableCharacterExceptDoubleQuote>  ; 字符串中的字符，除了双引号
 * <letter> ::= "a"..."z" | "A"..."Z"  ; 字母
 * <digit> ::= "0"..."9"  ; 数字
 * <type> ::= "number" | "string" | <identifier>  ; 假设类型可以是内置类型或用户定义类型
 * <iterable> ::= <expression>  ; 可迭代对象，目前只支持表达式
 * @endcode
 * */

#ifndef VARLEX_PARSER_H
#define VARLEX_PARSER_H
#pragma once

#include "../lexer/lexer.h"
#include "node.h"

class Parser {
    private:
        std::vector<std::unique_ptr<Token>>& tokens;
        size_t pos;
        void advance();
        void expect(TokenType type, const std::string& value = "");
        std::unique_ptr<Token> peek();
        void parseProgram();
        void parseSTMT();
        void parseAssign();
        void parseOutput();
        void parseControlFlow();
        void parseIfSTMT();
        void parseForLoop();
        void parseWhileLoop();
        void parseFunctionDef();
        void parseParameterList();
        void parseDefaultParameterList();
        void parseClassDef();
        void parseMemberVariableDeclarations();
        void parseBlock();
        void parseExpression();
        void parseTerm();
        void parseFactor();
    public:
        explicit Parser(std::vector<std::unique_ptr<Token>>& tokens);
        void parse();
};

#endif  // VARLEX_PARSER_H
