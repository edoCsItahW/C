// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file example.h
 * @author: edocsitahw
 * @version: 1.1
 * @date: 2024/09/27 下午12:11
 * @brief: 这是一个示例头文件。
 * @copyright: CC BY-NC-SA
 * @fileinfo
 * @since 1.0
 */

/**
 * @dir src
 * 源代码目录。
 *
 * 包含了示例头文件和源文件。
 * */

/**
 * @page page1 页面1
 * @mainpage Doxygen示例
 * @showdate "%Y-%m-%d %H:%M:%S" 2024-09-27 12:11:00
 *
 * @tableofcontents{nested:2}
 *
 * @subpage page2
 *
 * @section intro_sec 简介
 *
 * @subsection what_is_doxygen Doxygen是什么？
 *
 * @subsubsection what_is_doxygen_1 Doxygen是一款什么样的文档生成工具？
 *
 * @paragraph what_is_doxygen_2 Doxygen可以用来生成多种格式的文档，包括HTML、LaTeX、RTF、man pages、XML、CHM、PostScript、PDF等。
 *
 * @subparagraph what_is_doxygen_3 Doxygen可以从注释中提取代码信息，并生成格式良好的文档。
 *
 * @subsubparagraph what_is_doxygen_4 Doxygen可以自动生成文档的索引，并支持多种输出格式。
 *
 * @internal
 *      这是内部注释。
 *      @note 这是一个内部注释。
 * @endinternal
 *
 * @important 重要信息。
 * @if \~english
 * Doxygen is a documentation system for C++, C, Java, IDL (Corba, Microsoft, and UNO/OpenOffice flavors), and PHP. It
 * @elseif \~chinese
 * Doxygen 是一款 C、C++、Java、IDL（Corba、Microsoft、OpenOffice 等）、PHP 等语言的文档生成工具。它
 * @endif
 *
 * Doxygen是一个开源的文档生成工具，它可以从注释中提取代码信息，并生成格式良好的文档。
 *
 * @ref ExampleNamespace 命名空间。
 * @ref ExampleNSP 命名空间。
 *
 * @cite book1 这是一个参考文献。
 *
 * @link https://www.doxygen.nl/index.html Doxygen官网。@endlink
 *
 * exe实现
 * @arg @c --help 显示帮助信息。
 * @li @c --config 显示配置文件。
 * @arg @c --version 显示版本信息。
 *
 * @verbatim
 * 这是一段示例代码。
 * @endverbatim
 *
 * @code{.cpp}
 * int main() {
 *     std::cout << "Hello, world!" << std::endl;
 *     }
 * @endcode
 *
 * @dot
 * digraph G {
 *     a  -> b[ label="class A" ];
 *     b -> c;
 *     c
 * }
 * @enddot
 *
 * @msc
 * Sender -> Receiver [ label="Message" ];
 * @endmsc
 *
 * @image html logo.png "Logo"
 * 需要设置IMAGE_PATH，否则无法显示图片。
 *
 * @bug 没有bug
 * */

#ifndef VARLEX_EXAMPLE_H
#define VARLEX_EXAMPLE_H
#pragma once

#include <iostream>

/**
 * @defgroup example_group 示例组
 * @brief 这是示例组的简要描述。
 * @{
 * */

/**
 * @def EXAMPLE_MACRO
 * @brief 这是示例宏。位于行@lineinfo
 * @pre 宏定义前执行的语句。
 * @post 宏定义后执行的语句。
 * @remarks 备注。
 * */
#define EXAMPLE_MACRO 100

/**
 * @def EXAMPLE_MACRO_2
 * @brief 这是示例宏,将@b a 和 @b b 相加。
 * @param[in] a 第一个参数。
 * @par b大部分时候是第二个参数。
 * @param[out] b 第二个参数。
 * @return 返回值类型。
 * @deprecated 已弃用。
 */
#define EXAMPLE_MACRO_2(a, b) (a + b)

/** @} */

/**
 * @brief 这是一段示例函数的注释。
 * @param a 第一个参数。
 * @param b 第二个参数。
 * @return 返回值类型。
 * @note 这是一个示例函数的注释。
 * @dontinclude example.cpp
 * 主要功能
 * @skip main
 * @until {
 * 首先创建...
 * @skipline ...
 * 然后...
 * @line 示例
 * 之后
 * @line }
 */
int exampleFunction(int a, int b);

/**
 * @example exampleFunction example.cpp
 * @brief 这是一段示例代码。
 * */

/**
 * @brief 这是一段示例类的注释。
 * @details 这是一个示例类的详细描述。
 * @qualifier inline
 */
inline int exampleInlineFunction(int a, int b);

/**
 * @concept ExampleConcept
 *
 * @tparam T 类型参数。
 * @brief 这是一段示例概念的注释。
 * @details 这是一个示例概念的详细描述。
 * @note 该概念要求类型T支持加法操作。
 * */
template<typename T>
concept ExampleConcept = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

/**
 * @enum ExampleEnum
 * @brief 这是一段示例枚举的注释。
 * @details 这是一个示例枚举的详细描述。
 * */
enum class ExampleEnum {
    EXAMPLE_ENUM_VALUE_1,  ///< 示例枚举值1。
    EXAMPLE_ENUM_VALUE_2,  ///< 示例枚举值2。
};

/**
 * @class Base example.h "example.h"
 * @brief 抽象基类。
 * @details 这是一个抽象基类。
 * @attention 注意事项。
 * @pure
 * */
class Base {
    public:
        virtual void exampleMethod() = 0;
};

/// @cond DEV
void devFunction() {}
/// @endcond

/**
 * @class ExampleClass example.h "example.h"
 * @brief 这是一段示例类的注释。
 * @details 这是一个示例类的详细描述。
 * @extends Base
 * */
class ExampleClass {
    public:
        /**
         * @brief 该方法的注释。
         * @public @memberof ExampleClass
         * @overload void exampleMethod(int a, int b)
         * @param a 第一个参数。
         * @param b 第二个参数。
         * @tparam T 类型参数。
         * @return 返回值类型。
         * */
        template<ExampleConcept T>
        void exampleMethod(T a, T b);
        /**
         * @brief 该方法的注释。
         * @public @memberof ExampleClass
         * @static
         * @raisewarning 警告信息。
         * @exception std::exception 异常类。
         * @return 返回值类型。
         * */
        static void exampleStaticMethod();
        /**
         * @brief 友元函数的注释。
         * @public @memberof ExampleClass
         * */
        friend void exampleFriendMethod();
        /// @cond TEST
        int exampleTest();
        /// @endcond
    private:
        /**
         * @privatesection
         * @brief 这是私有成员函数的注释。
         * */
         void examplePrivateMethod();
         /**
          * @brief 这是私有成员变量的注释。
          * @private @memberof ExampleClass
          * */
          int examplePrivateVariable;
};

/**
 * @def EXAMPLE_MACRO_3
 * @brief 这是一个被追加到分组的示例宏。
 * @param a 第一个参数。
 * @param b 第二个参数。
 * @return 返回值类型。
 * @retval 0 成功。
 * @see EXAMPLE_MACRO_2
 * @ingroup example_group
 * */
#define EXAMPLE_MACRO_3(a, b) (a + b)

/**
 * @brief 这是一段示例友元函数的注释。
 * @details 这是一个示例友元函数的详细描述。
 * @related ExampleClass
 * */
void exampleFriendMethod() {}

/**
 * @name ExampleNamespace
 * @brief 这是示例命名空间的简要描述。
 * @{
 * */

/**
 * @anchor ExampleNSP
 * @namespace exampleNamespace
 * @brief 这是示例命名空间。
 */
namespace exampleNamespace {}

/** @} */

#endif  // VARLEX_EXAMPLE_H
