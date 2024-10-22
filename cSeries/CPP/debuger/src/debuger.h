// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file debuger.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/10 下午4:42
 * @brief 调试器API头文件
 * @copyright CC BY-NC-SA 2024. All rights reserved.
 * */

/** @mainpage 调试器API文档
 *
 * @tableofcontents
 *
 * @section intro_sec 简介
 * 该文档介绍了调试器API的使用方法和接口定义.
 *
 * @section product_sec 产品介绍
 * 该调试器是基于C++17-C++23标准编写的模板类,用于帮助开发者调试代码.
 *
 * @section install_sec 安装说明
 *
 * @subsection step1 获取
 * ...
 *
 * @subsection step2 编译
 * 在终端中进入到调试器源码目录,执行以下命令编译:
 * ...
 *
 * @section file_sec 文件列表
 * - @ref debuger.h
 * - @ref debuger.cpp
 * @section ref_sec 参考资料
 * - 无
 * @section license_sec 版权信息
 * - 版权所有 © 2024 Xiao Songtao.
 * - 保留一切权利。
 * - 联系作者：2207150234@st.sziit.edu.cn
 * */

#ifndef TEST_DEBUGER_H
#define TEST_DEBUGER_H
#pragma once

#include <iostream>
#include <source_location>
#include <utility>

#ifdef DLL_BUILD
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __declspec(dllimport)
#endif

/** @namespace debuger
 * @brief 调试器命名空间
 * @details 该命名空间包含调试器模板类Debuger
 * @see debuger::Debuger
 * */
namespace debuger {
    /** @concept Callable
     * @brief 可调用类型概念
     * @details 该概念用于判断 @a F 是否为可调用类型
     * @tparam F 待调试函数类型
     * */
    template<typename F>
    concept Callable = std::is_invocable_v<F>;

    /** @class Debuger
     * @brief 调试器模板类
     * @tparam F 待调试函数类型
     * @tparam Args 参数类型
     * @tparam R 返回值类型
     * @pre 如果 @a F 为成员函数,需先定义该类的实例
     * @todo 支持被装饰后的新函数支持loc调试参数,以确保调试信息是使用函数时,而不是装饰函数时生成的
     *
     * ## 示例
     *
     * ### 普通函数
     *
     * @code
     * int add(int a, int b) { return a + b; }
     *
     * int main() {
     *     Debuger<int(int, int)> debuger(add);  // 位置参数loc默认值为std::source_location::current()
     *     debuger(1, 2);  // 调用add函数并打印调试信息
     *     return 0;
     * }
     * @endcode
     *
     * ### 成员函数
     *
     * @code
     * class A {
     * public:
     *     int add(int a, int b) { return a + b; }
     *     int refFunc(int a, int b) {
     *         auto debuger = std::bind(&A::add, this, std::placeholders::_1, std::placeholders::_2);  // 绑定成员函数
     *         return debuger(a, b);
     *     }
     * };
     *
     * int main() {
     *     A a;
     *     // 使用std::bind绑定成员函数
     *     auto debuger = std::bind(&A::add, &a, std::placeholders::_1, std::placeholders::_2);  // 绑定成员函数
     *     debuger(1, 2);  // 调用A::add函数并打印调试信息
     *
     *     // 使用lambda表达式绑定成员函数
     *     auto debuger = [&a](int _a, int _b) { return a.add(_a, _b); };
     *     debuger(1, 2);  // 调用A::add函数并打印调试信息
     *     return 0;
     * }
     * @endcode
     * */
    template<typename R, typename... Args>
    class EXPORT Debuger {
    public:
        /** @typedef F
         * @brief 待调试函数类型
         * @details 该类型为函数指针类型,指向待调试函数的地址
         * @public @memberof Debuger
         * */
        using F = R (*)(Args...);
        /**
         * @brief 调试器模板类构造函数
         * @tparam R 返回值类型
         * @tparam Args 参数类型
         * @param func 待调试函数
         * @param loc 代码位置信息
         * @remark loc参数默认值为std::source_location::current(),即当前代码位置信息
         * */
        explicit Debuger(F func, std::source_location loc = std::source_location::current());

        /**
         * @brief 调试器模板类调用运算符
         * @tparam Args 参数类型
         * @param args 调用参数
         * @return 返回值类型
         * */
        R operator()(Args&&... args);

    private:
        /** @var _func
         * @brief 待调试函数
         * @details 该成员变量保存待调试函数的地址
         * @private @memberof Debuger
         * */
        F _func;
        /** @var _loc
         * @brief 代码位置信息
         * @details 该成员变量保存代码位置信息
         * @private @memberof Debuger
         * */
        std::source_location _loc;
    };

}  // namespace debuger

#include "debuger.hpp"

#endif  // TEST_DEBUGER_H

//    template<Callable F>
//    class Debuger {
//    public:
//        explicit Debuger(F func, std::source_location loc = std::source_location::current());
//
//        template<typename... Args>
//        auto operator()(Args&&... args) -> decltype(auto);  // std::declval<F>(std::forward<Args>(args)...)
//
//    private:
//        F _func;
//        std::source_location _loc;
//    };
