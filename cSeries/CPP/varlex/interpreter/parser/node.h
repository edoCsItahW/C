// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file node.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/09/22 下午8:36
 * @brief 该文件定义了VarLex的语法树节点.
 * @copyright CC BY-NC-SA
 * */

/**
 * @page AST 抽象语法树
 *
 * @section 简介
 *
 * */

#ifndef VARLEX_NODE_H
#define VARLEX_NODE_H
#pragma once

// FunctionDef(identifier name, arguments args, stmt* body, expr* decorator_list, expr? returns, string? type_comment)
// AsyncFunctionDef(identifier name, arguments args, stmt* body, expr* decorator_list, expr? returns, string? type_comment)
// ClassDef(identifier name, expr* bases, keyword* keywords, stmt* body, expr* decorator_list)
// Return(expr? value)
// Delete(expr* targets)
// Assign(expr* targets, expr value, string? type_comment)
// AugAssign(expr target, operator op, expr value)
// AnnAssign(expr target, expr annotation, expr? value, int simple)
// For(expr target, expr iter, stmt* body, stmt* orelse, string? type_comment)
// AsyncFor(expr target, expr iter, stmt* body, stmt* orelse, string? type_comment)
// While(expr test, stmt* body, stmt* orelse)
// If(expr test, stmt* body, stmt* orelse)
// With(withitem* items, stmt* body, string? type_comment)
// AsyncWith(withitem* items, stmt* body, string? type_comment)
// Match(expr subject, match_case* cases)
// Raise(expr? exc, expr? cause)
// Try(stmt* body, excepthandler* handlers, stmt* orelse, stmt* finalbody)
// TryStar(stmt* body, excepthandler* handlers, stmt* orelse, stmt* finalbody)
// Assert(expr test, expr? msg)
// Import(alias* names)
// ImportFrom(identifier? module, alias* names, int? level)
// Global(identifier* names)
// Nonlocal(identifier* names)
// Expr(expr value)
// Pass
// Break
// Continue

#include "../lexer/lexer.h"
#include <cstring>
#include <memory>

/**
 * @defgroup AST 语法树节点
 * @brief 该模块定义了VarLex的语法树节点.
 * */

/** @concept ConstType
 * @brief 常量类型
 * @details 常量类型包括:
 *      - const char*
 *      - const std::string&
 *      - const std::string
 *      - std::string
 *      - int
 *      - double
 *
 * @tparam T 常量类型
 * */
template<typename T>
concept ConstType = std::is_same_v<T, const char*> || std::is_same_v<T, const std::string&> || std::is_same_v<T, const std::string> || std::is_same_v<T, std::string> || std::is_same_v<T, int>
    || std::is_same_v<T, double>;

namespace AST {
    class ASTNode;
    class STMT;
    class Assign;
    class Output;
    class ControlFlow;
    class IfSTMT;
    class ForLoop;
    class WhileLoop;
    class FunctionDef;
    class ClassDef;
    class Block;
    class Expression;
    class Identifier;
    class Literal;

    /**
     * @class AST
     * @brief AST节点基类
     * @details 该类是所有AST节点的基类.
     * */
    struct ASTNode {
            /**
             * @brief 节点名称
             * @details 节点名称, toString()会使用该名称打印节点信息.
             * @public @memberof AST
             * @invariant 该名称在程序编写时已经确定, 不会随着程序的运行而改变.
             * @qualifier const
             * @see toString()
             * */
            const char* nodeName;
            /**
             * @brief 构造函数
             * @details 该构造函数用于初始化 @ref nodeName 属性
             * */
            ASTNode();
            /** @brief 打印节点信息
             * @details 打印节点信息, 包括节点名称和节点值.
             * @param args @b 节点名 和 @b 节点值
             * @return std::string 节点信息
             * @note 建议传入格式为 `"name: value"`
             * @remark 由于模板参数推导机制,该函数的实现位于 @ref node.tpp 文件中.
             * */
            std::string toString(auto&&... args) const;
    };

    /**
     * @defgroup STMT 语句节点
     * @brief 该模块定义了VarLex的语句节点.
     * @ingroup AST
     * @{
     * */

    /**
     * @class STMT
     * @brief 语句节点基类
     * @details 该类是所有语句节点的基类,现支持以下语句:
     *      - FunctionDef: 函数定义
     *      - ClassDef: 类定义
     *      - Return: 返回语句
     *      - Delete: 删除语句
     *      - Assign: 赋值语句
     *      - AugAssign: 增量赋值语句
     *      - For: 循环语句
     *      - While: 条件循环语句
     *      - If: 条件语句
     *      - With: 条件语句(with语句)
     *      - Match: 匹配语句
     *      - Raise: 异常抛出语句
     *      - Try: 异常处理语句
     *      - TryStar: 异常处理语句(try-except语句)
     *      - Assert: 断言语句
     *      - Import: 导入语句
     *      - ImportFrom: 导入语句(from语句)
     *      - Global: 全局声明
     *      - Nonlocal: 局部声明
     *      - Expr: 表达式语句
     *      - Pass: 空语句
     *      - Break: 跳出循环语句
     *      - Continue: 跳过循环语句
     * 待支持的语句:
     *      - AsyncFunctionDef: 异步函数定义
     *      - ClassDef: 类定义
     *      - AnnAssign: 类型注解赋值语句
     *      - AsyncFor: 异步循环语句
     *      - AsyncWith: 异步条件语句
     *      - Global: 全局声明
     *      - Nonlocal: 局部声明
     * @todo 实现待支持的语句
     * */
    struct STMT : public ASTNode {
            /**
             * @var body
             * @brief 语句体
             * @details 语句体,以vector形式存储语句的各个子节点.
             * @public @memberof STMT
             * @qualifier pointer
             * */
            std::vector<std::unique_ptr<ASTNode>> body;
            /**
             * @brief 构造函数
             * @details 该构造函数用于初始化 @ref body 属性
             * @param _body 语句体
             * */
            explicit STMT(std::vector<std::unique_ptr<ASTNode>> _body = {});
            /** @brief 打印节点信息
             * @details 打印节点信息, 包括节点名称和节点值.
             * @param args @b 节点名 和 @b 节点值
             * @return std::string 节点信息
             * @note 建议传入格式为 `"name: value"`
             * @remark 由于模板参数推导机制,该函数的实现位于 @ref node.tpp 文件中.
             * */
            std::string toString(auto&&... args) const;
    };

    struct Assign : public STMT {
            std::unique_ptr<STMT> target;
    };
    
    struct Output : public STMT {};
    
    struct ControlFlow : public STMT {};
    
    struct IfSTMT : public ControlFlow {};
    
    struct ForLoop : public ControlFlow {};
    
    struct WhileLoop : public ControlFlow {};
    
    /**
     * @class FunctionDef
     * @brief 函数定义节点
     * @details 该类是函数定义节点, 用于表示函数定义语句.
     * ## 暂定VarLex的函数语法:
     * @code
     * functionName[type1, type2,..., typeN | kwtype1, kwtype2,..., kwtypeM](arg1, arg2: default1,..., argN, kwarg1, kwarg2: default2,..., kwargM: valueM) -> returnType {}
     * @endcode
     * @see STMT
     * */
    struct FunctionDef : public ASTNode {
            /**
             * @brief 函数名
             * @details 函数名, 字符串形式.
             * @public @memberof FunctionDef
             * @qualifier const
             * @invariant 该名称在构造函数中确定,不应进行修改.
             * @note 函数名应该遵循标识符命名规则.
             * */
            const std::string name;
            /**
             * @var args
             * @brief 函数参数
             * @details 函数参数, 由 @ref Arguments 类表示.
             * @public @memberof FunctionDef
             * @qualifier pointer
             * @pre 该指针不为 nullptr,并进行make_unique()操作.
             * */
//            std::unique_ptr<> args;
            std::vector<std::unique_ptr<Expression>> decoratorList;
            std::unique_ptr<Expression> returns;
    };

    struct ClassDef : public ASTNode {
            std::string name;
            std::vector<std::string> bases;
            std::vector<std::unique_ptr<Expression>> decoratorList;
    };

        
    struct Block : public ASTNode {};
    /** @} */

    struct Expression : public ASTNode {
            explicit Expression(std::vector<std::unique_ptr<ASTNode>> _body = {});
    };
    
    struct Identifier : public ASTNode {};
    
    struct Literal : public ASTNode {};

    struct Arguments : public ASTNode {
            std::vector<std::unique_ptr<Expression>> args;
            std::vector<std::unique_ptr<Expression>> defaults;
            std::vector<std::unique_ptr<Expression>> kwonlyargs;
            std::vector<std::unique_ptr<Expression>> kwdefaults;
            std::unique_ptr<Expression> vararg;
            std::unique_ptr<Expression> kwarg;
    };

    struct Expr : public STMT {
            explicit Expr(std::vector<std::unique_ptr<ASTNode>> _body = {});
    };

    template<ConstType T>
    struct Constant : public Expression {
        public:
            T value;
            TokenType type;
            Constant(T value, TokenType type);
            [[nodiscard]] std::string toString() const;
    };

}  // namespace AST

#include "node.tpp"

#endif  // VARLEX_NODE_H
