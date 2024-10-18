// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include <format>


namespace py = pybind11;

/**
 * @brief 定义Python模块
 * @param m Python模块
 * */
PYBIND11_MODULE(quesParser, m) {
    m.doc() = "A Parser for parsing questions in C++";

    /**
     * @defgroup pyApi Python接口
     * @brief 暴露给Python的接口
     * @{
     * */

    /**
     * @brief 定义TokenType枚举类型
     * */
    py::enum_<TokenType>(m, "TokenType")
        .value("INDEX", TokenType::INDEX)
        .value("LETTER", TokenType::LETTER)
        .value("CONTENT", TokenType::CONTENT)
        .value("NEWLINE", TokenType::NEWLINE)
        .value("DOT", TokenType::DOT)
        .value("END", TokenType::END)
        .value("INVALID", TokenType::INVALID)
        .export_values();

    /**
     * @brief 定义tokenTypeNames数组，用于将TokenType枚举类型转换为字符串
     * */
    m.attr("tokenTypeNames") = py::cast(tokenTypeNames);

    /**
     * @brief 定义Token类，用于封装词法分析器生成的token
     * */
    py::class_<Token>(m, "Token")
        .def(py::init<TokenType, size_t, std::string>(), "Construct a Token object", py::arg("type"), py::arg("pos"), py::arg("value"))
        .def_readwrite("type", &Token::type)
        .def_readwrite("pos", &Token::pos)
        .def_readwrite("value", &Token::value)
        .def("__repr__", [](const Token& t) { return std::format("Token<{}>({}, {})", t.pos, tokenTypeNames[static_cast<int>(t.type)], t.value); });

    /**
     * @brief 定义Lexer类，用于词法分析
     * */
    py::class_<Lexer>(m, "Lexer")
        .def(py::init<std::string>(), "Construct a Lexer object from a string", py::arg("text"))
        .def("__next__", &Lexer::operator*)
        .def_static("tokenize", &Lexer::tokenize, "Tokenize a string into a vector of Token objects", py::arg("text"));

    /**
     * @brief 定义ast::Content类，用于封装语法分析器生成的Content节点
     * */
    py::class_<ast::Content>(m, "Content")
        .def(py::init<std::string>(), "Construct a Content object from a string", py::arg("value"))
        .def_readwrite("value", &ast::Content::value);

    /**
     * @brief 定义ast::Option类，用于封装语法分析器生成的Option节点
     * */
    py::class_<ast::Option>(m, "Option")
        .def(py::init<Token, Token, ast::Content>(), "Construct an Option object from a Token and a Content object", py::arg("letter"), py::arg("dot"), py::arg("content"))
        .def_readwrite("letter", &ast::Option::letter)
        .def_readwrite("dot", &ast::Option::dot)
        .def_readwrite("content", &ast::Option::content);

    /**
     * @brief 定义ast::Question类，用于封装语法分析器生成的Question节点
     * */
    py::class_<ast::Question>(m, "Question")
        .def(py::init<Token, Token, ast::Content>(), "Construct a Question object from a Token and a vector of Option objects")
        .def_readwrite("index", &ast::Question::index)
        .def_readwrite("dot", &ast::Question::dot)
        .def_readwrite("content", &ast::Question::content);

    /**
     * @brief 定义ast::Block类，用于封装语法分析器生成的Block节点
     * */
    py::class_<ast::Block>(m, "Block")
        .def(py::init<ast::Question, std::vector<ast::Option>>(), "Construct a Block object from a Question and a vector of Option objects")
        .def_readwrite("question", &ast::Block::question)
        .def_readwrite("options", &ast::Block::options);

    /**
     * @brief 定义ast::Paper类，用于封装语法分析器生成的Paper节点
     * */
    py::class_<ast::Paper>(m, "Paper")
        .def(py::init<std::vector<ast::Block>>(), "Construct a Paper object from a vector of Block objects")
        .def_readwrite("blocks", &ast::Paper::blocks);

    /**
     * @brief 定义Parser类，用于语法分析
     * */
    py::class_<Parser>(m, "Parser")
        .def(py::init<std::vector<Token>>(), "Construct a Parser object from a vector of Token objects", py::arg("tokens"))
        .def("parse", &Parser::parse);

    py::class_<ParseException>(m, "ParseException")
        .def(py::init<std::string>(), "Construct a ParseException object from a string and a position", py::arg("msg"))
        .def("what", &ParseException::what);
    /** @} */
}
