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
 * @date 2024/10/10 下午10:12
 * @brief 题目解析器的语法分析器API头文件
 * @copyright CC BY-NC-SA
 * */

#ifndef DEBUGER_PARSER_H
#define DEBUGER_PARSER_H
#pragma once

#include "../exception/exception.h"
#include "../lexer/lexer.h"
#include <optional>

/**
 * @page Parser 语法分析器
 *
 * @section grammar EBNF文法
 * @code{.ebnf}
 * Paper ::= Block*
 * Block ::= Ques Option*
 * Question ::= Index '.' Content
 * Option ::= Letter '.' Content
 * Content ::= { Charecter | '\\n' }
 * Index ::= DIGIT+
 * Letter ::= 'A' | 'B' | 'C' | 'D'
 * Digit ::= '0' ... '9'
 * Charecter ::= ?any character?
 * @endcode
 * */

/** @namespace ast 语法分析器的抽象语法树
 * @brief 语法分析器的抽象语法树
 * @details 语法分析器的抽象语法树由以下结构组成:
 * - @ref ast::Content "Content": 题目或选项的内容
 * - @ref ast::Option "Option": 选项
 * - @ref ast::Question "Question": 题目
 * - @ref ast::Block "Block": 题目块
 * - @ref ast::Paper "Paper": 试卷
 * */
namespace ast {
    /** @struct Content
     * @brief 题目或选项的内容
     * @details 题目或选项的内容由一个字符串组成,该字符串不应包含换行符.
     * */
    struct Content {
        /** @var value
         * @brief 内容的字符串
         * @details 内容的字符串,不应包含换行符.
         * @public @memberof Content
         * */
        std::string value;
    };

    /** @struct Option
     * @brief 选项
     * @details 选项由一个字母和一个内容组成.
     * */
    struct Option {
        /** @var letter
         * @brief 选项的字母
         * @details 选项的字母,字母只能是'A', 'B', 'C', 'D'.
         * @public @memberof Option
         * @see Token
         * */
        Token letter;
        /** @var dot
         * @brief 选项后接的分隔符'.'
         * @details 选项后接的分隔符'.',如: @p A.选项内容.
         * @public @memberof Option
         * @note 在题目中,'.'可以省略,语法分析器会自动补全.
         * @see Token
         * */
        Token dot;
        /** @var content
         * @brief 选项的内容
         * @public @memberof Option
         * @see Content
         * */
        Content content;
    };

    /** @struct Question
     * @brief 题目
     * @details 题目由一个索引和一个内容组成.
     * */
    struct Question {
        /** @var index
         * @brief 题目的索引
         * @details 题目的索引,索引是一个数字字符串.
         * @public @memberof Question
         * @see Token
         * */
        Token index;
        /** @var dot
         * @brief 题目后接的分隔符'.'
         * @details 题目后接的分隔符'.',如: @p 1.题目内容.
         * @public @memberof Question
         * @note 在题目中,'.'可以省略,语法分析器会自动补全.
         * @see Token
         * */
        Token dot;
        /** @var content
         * @brief 题目的内容
         * @public @memberof Question
         * @see Content
         */
        Content content;
    };

    /** @struct Block
     * @brief 题目块
     * @details 题目块由一个题目和若干选项组成.
     * */
    struct Block {
        /** @var question
         * @brief 题目
         * @public @memberof Block
         * @note 题目可以没有,即空题目块.
         * @see Question
         * */
        std::optional<Question> question;
        /** @var options
         * @brief 选项列表
         * @public @memberof Block
         * @see Option
         * */
        std::vector<Option> options;
    };

    /** @struct Paper
     * @brief 试卷
     * @details 试卷由若干题目块组成.
     * */
    struct Paper {
        /** @var blocks
         * @brief 题目块列表
         * @public @memberof Paper
         * @see Block
         * */
        std::vector<Block> blocks;
    };
}  // namespace ast

/** @class Parser
 * @brief 语法分析器
 * @details 语法分析器的主要功能是将词法分析器产生的词法单元列表转换为抽象语法树.
 * @pre 应先调用词法分析器,生成词法单元列表.
 * ## 示例
 * @code{.cpp}
 * #include "parser.h"
 * #include "lexer.h"
 *
 * int main() {
 *     std::string input = "1.题目内容\nA.选项内容\nB.选项内容\nC.选项内容\nD.选项内容";
 *
 *     auto tokens = Lexer::tokenize(input);
 *     Parser parser(tokens);
 *     ast::Paper paper = parser.parse();
 *     // 处理抽象语法树...
 *     return 0;
 * }
 * @endcode
 * */
class Parser {
private:
    /** @var type
     * @brief 令牌类型别名
     * */
    using Type = TokenType;
    /** @var _tokens
     * @brief 词法单元列表
     * @details 词法单元列表,由词法分析器生成.
     * @invariant 词法单元列表不应修改.
     * @private @memberof Parser
     * */
    std::vector<Token> _tokens;
    /** @var _pos
     * @brief 当前词法单元的位置
     * @details 当前词法单元的位置,初始值为0.
     * @private @memberof Parser
     * */
    size_t _pos;
    /**
     * @brief 移动消耗
     * @details 确定当前词法单元是否为指定类型,如是则移动消耗,否则抛出异常.
     * @param type 期望的词法单元类型
     * @throw std::runtime_error 当当前词法单元类型与期望类型不符时
     * @private @memberof Parser
     */
    void consume(Type type, std::source_location loc = std::source_location::current());
    /**
     * @brief 解析一个题目块
     * @details 解析一个题目块,包括题目和选项.
     * @return 题目块的抽象语法树
     * @private @memberof Parser
     */
    ast::Block parseBlock();
    /**
     * @brief 解析一个题目
     * @details 解析一个题目,包括索引和内容.
     * @return 题目的抽象语法树
     * @private @memberof Parser
     * @warning 返回值可能为空,即空题目块.
     */
    std::optional<ast::Question> parseQuestion();
    /**
     * @brief 解析一个选项
     * @details 解析一个选项,包括字母和内容.
     * @return 选项的抽象语法树
     * @private @memberof Parser
     */
    ast::Option parseOption();
    /**
     * @brief 解析内容
     * @details 解析内容,包括一个字符串.
     * @return 内容的抽象语法树
     * @private @memberof Parser
     */
    ast::Content parseContent();

public:
    /**
     * @brief Parser的构造函数
     * @param tokens 词法单元列表
     * @details 构造函数,传入词法单元列表.
     * @private @memberof Parser
     * */
    explicit Parser(std::vector<Token> tokens);
    /**
     * @brief 解析抽象语法树
     * @details 解析抽象语法树,包括试卷.
     * @return 试卷的抽象语法树
     * */
    ast::Paper parse();
};

#endif  // DEBUGER_PARSER_H
