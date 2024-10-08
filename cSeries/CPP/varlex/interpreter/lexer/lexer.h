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
 * @date 2024/09/21 下午1:59
 * @brief 该文件定义了词法分析器的接口
 * @copyright CC BY-NC-SA
 * */

/**
 * @mainpage VarLex语言解释器
 *
 * @tableofcontents{nested:2}
 *
 * @section 简介
 * VarLex语言解释器是VarLex语言的解释器,它可以将VarLex语言的源代码转换为中间代码,并执行中间代码.
 *
 * @section 目录
 * - @subpage Lexer 词法分析器
 * */

#ifndef DFIMPL_LEXER_H
#define DFIMPL_LEXER_H
#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <map>
#include <vector>
#include <format>
#include "../../vdb/vdb.h"
#include "../../exception/exception.h"

/** @brief 路径补全
 *
 * @details 如果输入字符串是 @b 文件名 或者 @b 相对路径 ,则补全路径
 *
 * @param str 输入字符串
 * @return 补全后的路径
 * @throw filesystem_error 当路径不存在时主动抛出异常
 */
std::string completePath(const std::string& _str);

/** @brief 从文件中读取内容.
 *
 * @param fileName 文件名
 * @return 文件内容
 * @note 仅支持 `*.vl` 文件
 * @throws invalid_argument 当文件后缀不是 `*.vl` 时抛出异常
 * @exception runtime_error 无法打开文件时抛出异常
 * */
std::string readFile(const std::string& _fileName);

/** @enum TokenType
 *
 * @brief 定义了词法分析器的Token类型
 *
 * @warning 该枚举成员顺序与TokenName数组中的名称一一对应,请勿随意修改
 * @remark
 *     - @ref Lexer::extractOperator() 识别大部分运算符,
 *     - @ref Lexer::extractIdentifier() 识别标识符,
 *     - @ref Lexer::extractNumber() 识别数字,
 *     - @ref Lexer::extractString() 识别字符串,
 *     - @ref Lexer::extractComment() 识别注释
 * */
enum class TokenType {
    // 标志符
    END,  ///< 结束符

    // 算术运算符
    ADD,  ///< \+
    SUB,  ///< \-
    MUL,  ///< \*
    DIV,  ///< /
    INC,  ///< ++
    DEC,  ///< --
    MOD,  ///< %

    // 赋值运算
    ADD_ASSIGN,  ///< +=
    SUB_ASSIGN,  ///< -=
    MUL_ASSIGN,  ///< *=
    DIV_ASSIGN,  ///< /=

    // 关系运算
    EQ,  ///< ==
    NE,  ///< !=
    LT,  ///< <
    GT,  ///< \>
    LE,  ///< <=
    GE,  ///< >=
    NOT,  ///< !
    AND,  ///< &&
    OR,  ///< ||

    // 位运算
    LSHIFT,  ///< <<
    RSHIFT,  ///< \>>
    XOR,  ///< ^
    BITAND,  ///< &
    BITOR,  ///< |
    BITNOT,  ///< ~

    // 分隔
    COMMA,  ///< ,
    SEMICOLON,  ///< ;
    COLON,  ///< :
    LBRACE,  ///< {
    RBRACE,  ///< }
    LPAREN,  ///< (
    RPAREN,  ///< )
    LBRACKET,  ///< [
    RBRACKET,  ///< ]

    // 其它运算
    RARROW,  ///< ->
    LARROW,  ///< <-
    DOT,  ///< \.
    ELLIPSIS,  ///< ...
    QUESTION,  ///< ?
    AT,  ///< @
    DOLLAR,  ///< $
    HASH,  ///< \#

    // 类型
    SYMBOL,  ///< 符号
    NUMBER,  ///< 数字
    STRING,  ///< 字符串
    COMMENT,  ///< 注释
    ASSIGN,  ///< =
    IDENTIFIER,  ///< 标识符
    UNKNOWN,  ///< 未知类型
};

/**
 * @var TokenName
 * @brief 定义了Token类型对应的字符串表示
 * @warning 该数组成员顺序与TokenType枚举中的成员顺序一一对应,请勿随意修改
 * @invariant TokenName[i] == TokenName[static_cast<int>(TokenType::i)]
 * @qualifier const
 * */
static const char* TokenName[] = {
    "END",
    "ADD", "SUB", "MUL", "DIV", "INC", "DEC", "MOD",
    "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN",
    "EQ", "NE", "LT", "GT", "LE", "GE", "NOT", "AND", "OR",
    "LSHIFT", "RSHIFT", "XOR", "BITAND", "BITOR", "BITNOT",
    "COMMA", "SEMICOLON", "COLON", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
    "RARROW", "LARROW", "DOT", "ELLIPSIS", "QUESTION", "AT", "DOLLAR", "HASH",
    "SYMBOL", "NUMBER", "STRING", "COMMENT", "ASSIGN", "IDENTIFIER", "UNKNOWN",
};

/**
 * @struct Token
 * @brief 词法分析器的Token结构体
 * @details Token结构体包含了Token的类型和值,并重载了输出运算符,方便调试.
 * @todo 实现Token的拷贝构造函数和赋值运算符,也许还会添加更多有用的属性如行号,列号等.
 * */
struct Token {
    /**
     * @brief 该Token的类型
     * @public @memberof Token
     */
    TokenType type;
    /**
     * @brief 该Token的值
     * @public @memberof Token
     * */
    std::string value;
    /**
     * @brief 重载比较运算符
     * @details 重载了比较运算符,用于比较两个Token是否相等.
     * @public @memberof Token
     * @param other 另一个Token
     * @return bool 相等返回true,否则返回false
     * @qualifier const
     * */
    bool operator==(const Token& other) const;
    /**
     * @brief 重载输出运算符
     * @public @memberof Token
     * */
    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

/**
 * @class Lexer
 * @brief 词法分析器类
 * @details 该类实现了词法分析器的功能,可以将输入的字符串分割成Token序列.
 * ## 示例
 * @code
 * #include "lexer.h"
 *
 * int main() {
 *      // 从字符串中获取Token序列
 *      auto tokens = Lexer::tokenize("int a = 10 + 20 * 30 / 40;");
 *
 *      // 从文件中获取Token序列
 *      auto tokens = Lexer::tokenize(readFile("example.vl"));
 * }
 * @endcode
 * */
class Lexer {
    private:
        /**
         * @brief 解析目标字符串
         * @details 该属性是待分析的程序原文,由构造函数传入.
         * @private @memberof Lexer
         * @invariant 该字符串自读取后不会也不应被修改.
         * @qualifier const
         * */
        const std::string text;
        /**
         * @var pos
         * @brief 当前Token的位置
         * @details 该属性记录了当前Token的位置,由构造函数初始化为0,并在每次调用`operator++`时递增.
         * @private @memberof Lexer
         */
        size_t pos;
        /**
         * @brief 跳过空白字符
         * @details 该方法跳过输入字符串中的空白字符,包括空格,制表符,换行符等.
         * 其内是while循环,pos自增直到非空字符或结尾停止.
         * @private @memberof Lexer
         */
        void skipWhitespace();
        /**
         * @brief 解析数值类型
         * @details 循环读取数字字符,直到遇到非数字字符或结尾停止.
         * @private @memberof Lexer
         * @return Token 包含数字的Token
         * @note 这里的数值类型包括整数,浮点数,但区分整数和浮点数不是Lexer的任务
         * @todo 添加对科学计数法的支持
         */
        Token extractNumber();
        /**
         * @brief 解析单行注释类型
         * @details 循环读取注释字符,直到遇到`\\n`或结尾停止.
         * @private @memberof Lexer
         * @return Token 包含注释的Token
         * @todo 实现多行注释的解析
         * */
        Token extractComment();
        Token extractSymbol();
        Token extractIdentifier();
        Token extractOperator();
        Token extractString();

    public:
        explicit Lexer(std::string text);
        Token operator*();
        Lexer& operator++();
        Lexer operator++(int);
        Lexer& operator--();
        Lexer operator--(int);
        bool operator==(const char& c) const;
        bool operator!=(const char& c) const;
        char operator[](int i) const;
        static std::vector<std::unique_ptr<Token>> tokenize(const std::string& text);
};

#endif  // DFIMPL_LEXER_H
