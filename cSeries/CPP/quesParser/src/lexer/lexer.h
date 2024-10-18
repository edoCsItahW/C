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
 * @date 2024/10/10 下午9:59
 * @brief 题目解析器的词法分析器API头文件
 * @copyright CC BY-NC-SA
 * */

#ifndef DEBUGER_LEXER_H
#define DEBUGER_LEXER_H
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>

/**
 * @mainpage 题目解析器API文档
 * @tableofcontents{nested:2}
 * @section intro_sec 简介
 * 题目解析器,用于对题目文本进行词法分析和语法分析,已生成语法树.
 *
 * @section usage_sec 使用方法
 * @subsection py_usage Python使用方法
 * 1. 确保安装了quesParser包
 * @code
 * pip install quesParser
 * @endcode
 * 2. 使用示例
 * @code
 * import quesParser
 *
 * text = "1. A\n2. B\n3. C"
 * # 获取令牌集合
 * tokens = quesParser.Lexer.tokenize(text)
 * for token in tokens:
 *     print(token)
 *
 * # 获取语法树
 * tree = quesParser.Parser.parse(tokens)
 * for block in tree.blocks:
 *     print(block)
 * @endcode
 *
 * @subsection cpp_usage C++使用方法
 * 1. 获取quesParser静态库,及编译方法
 * @see https://github.com/edocsitahw/quesParser/releases
 * 2. 使用示例
 * @code
 * #include "lexer.h"
 * #include "parser.h"
 *
 * int main() {
 *     std::string text = "1. A\n2. B\n3. C";
 *
 *      // 获取令牌集合
 *     std::vector<Token> tokens = Lexer::tokenize(text);
 *     for (const auto& token : tokens) {
 *         std::cout << token << std::endl;
 *     }
 *     // 获取语法树
 *     auto tree = Parser::parse(tokens);
 *     for (const auto& block : tree->blocks) {
 *         std::cout << block << std::endl;
 *     }
 *     return 0;
 * }
 * @endcode
 *
 * @subpage Parser
 * */

/** @enum TokenType
 * @brief 令牌类型枚举
 * @details 定义了令牌类型,用于表示词法分析器识别出的各种令牌类型.
 * */
enum class TokenType {
    INDEX,  ///< 索引
    LETTER,  ///< 字母
    DOT,  ///< 点
    CONTENT,  ///< 内容
    NEWLINE,  ///< 换行符
    END,  ///< 结束符
    INVALID  ///< 无效
};

/** @var tokenTypeNames
 * @brief 令牌类型名称数组
 * @details 用于打印令牌类型名称.
 * @warning 该数组成员顺序与TokenType枚举中的成员顺序一一对应,请勿随意修改
 * @invariant 不应修改
 * @qualifier const
 * */
static const std::string tokenTypeNames[] = {"INDEX", "LETTER", "DOT", "CONTENT", "NEWLINE", "END", "INVALID"};

/** @struct Token
 * @brief 令牌结构体
 * @details 用于表示词法分析器识别出的各种令牌.
 * @todo 根据换行符数量,获取行号和列号
 * */
struct Token {
    /** @var type
     * @brief 令牌类型
     * @details 令牌类型,用于表示词法分析器识别出的各种令牌类型.
     * @public @memberof Token
     * */
    TokenType type;
    /** @var pos
     * @brief 令牌位置
     * @details 令牌在文本中的位置,用于定位错误.
     * @public @memberof Token
     * */
    std::pair<size_t, size_t> pos;
    /** @var value
     * @brief 令牌值
     * @details 令牌的值,用于表示索引,字母,内容等.
     * @public @memberof Token
     * */
    std::string value{};
    /**
     * @brief Token的字符串化方法
     * @details 用于打印Token的字符串方法.
     * @return std::string Token的字符串表示.
     * @public @memberof Token
     * */
    [[nodiscard]] std::string toString() const;
    /**
     * @brief 重载输出流运算符
     * @public @memberof Token
     * */
    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

/** @class Lexer
 * @brief 词法分析器类
 * @details 用于对题目文本进行词法分析,识别出各种令牌.
 * @note 该类不应被直接实例化,应使用Lexer::tokenize静态方法进行调用.
 * ## 示例
 * @code
 * #include "lexer.h"
 * int main() {
 *     std::string text = "1. A\n2. B\n3. C";
 *     std::vector<Token> tokens = Lexer::tokenize(text);
 *     for (const auto& token : tokens) {
 *         std::cout << token << std::endl;
 *     }
 *     return 0;
 * }
 * @endcode
 * @post 一般将令牌集合继续传递给语法分析器进行语法分析.
 * */
class Lexer {
private:
    /** @var type
     * @brief 令牌类型别名
     * */
    using type = TokenType;
    /** @var _text
     * @brief 题目文本
     * @details 待分析的题目文本.
     * @private @memberof Lexer
     * @invariant 该变量自读取后不应被修改.
     * @qualifier const
     * */
    const std::string _text;
    /** @var _pos
     * @brief 当前分析位置索引
     * @details 当前分析位置索引,用于指向待分析的文本的当前位置.
     * @private @memberof Lexer
     * */
    size_t _pos;
    /** @var _line
     * @brief 当前行号
     * @details 当前行号,用于定位错误.
     * @private @memberof Lexer
     * */
    size_t _line;
    /** @var _col
     * @brief 当前列号
     * @details 当前列号,用于定位错误.
     * @private @memberof Lexer
     * */
    size_t _col;
    /**
     * @brief 跳过空白字符
     * @details 跳过空白字符,包括空格,制表符等.
     * @remark 不包含换行符.
     * @private @memberof Lexer
     * */
    void skip();
    /**
     * @brief 解析'INDEX'令牌
     * @details 解析'INDEX'令牌,即题号.
     * @return Token 解析出的'INDEX'令牌.
     * @private @memberof Lexer
     * */
    Token extractIndex();
    /**
     * @brief 解析'LETTER'令牌
     * @details 解析'LETTER'令牌,即选项字母.
     * @return Token 解析出的'LETTER'令牌.
     * @private @memberof Lexer
     * */
    Token extractLetter();
    /**
     * @brief 解析'CONTENT'令牌
     * @details 解析'CONTENT'令牌,即题目或选项内容.
     * @return Token 解析出的'CONTENT'令牌.
     * @private @memberof Lexer
     * */
    Token extractContent();

public:
    /**
     * @brief Lexer的构造函数
     * @details 构造函数,用于初始化词法分析器.
     * @param text 题目文本
     * @private @memberof Lexer
     * @note 参数@p text 将会被std::move,因此不应在外部修改.
     * */
    explicit Lexer(std::string text);
    /**
     * @brief 重载解引用运算符
     * @details 重载解引用运算符,用于获取当前指向的令牌.
     * @return Token 当前指向的令牌.
     * @private @memberof Lexer
     * */
    Token operator*();
    /**
     * @brief 重载前缀递增运算符
     * @details 重载前缀递增运算符,用于指向下一个令牌.
     * @return Lexer 指向下一个令牌的词法分析器.
     * @private @memberof Lexer
     * @remark 与重载的解引用运算符不同,该运算符不会改变索引位置.
     * @bug 仅使用++_pos做了简单实现,实际结果是指向了下一个字符,而不是下一个令牌.
     * @todo 实现正确的后缀递增运算符,指向下一个令牌.
     * */
    Lexer& operator++();
    /**
     * @brief 重载后缀递增运算符
     * @details 重载后缀递增运算符,用于指向下一个令牌.
     * @return Lexer 指向下一个令牌的词法分析器.
     * @private @memberof Lexer
     * @bug 仅使用++_pos做了简单实现,可能结果不合预期.
     * */
    Lexer operator++(int);
    /**
     * @brief 重载前缀递减运算符
     * @details 重载前缀递减运算符,用于指向上一个令牌.
     * @return Lexer 指向上一个令牌的词法分析器.
     * @private @memberof Lexer
     * @bug 仅使用--_pos做了简单实现,实际结果是指向了上一个字符,而不是上一个令牌.
     * @todo 实现正确的后缀递减运算符,指向上一个令牌.
     * */
    Lexer& operator--();
    /**
     * @brief 重载后缀递减运算符
     * @details 重载后缀递减运算符,用于指向上一个令牌.
     * @return Lexer 指向上一个令牌的词法分析器.
     * @private @memberof Lexer
     * @bug 仅使用--_pos做了简单实现,可能结果不合预期.
     * */
    Lexer operator--(int);
    /**
     * @brief 静态方法tokenize
     * @details 静态方法tokenize,用于对题目文本进行词法分析,识别出各种令牌.
     * @param text 题目文本
     * @return std::vector<Token> 解析出的令牌集合.
     * @public @memberof Lexer
     * */
    static std::vector<Token> tokenize(const std::string& text);
};

#endif  // DEBUGER_LEXER_H
