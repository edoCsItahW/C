// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file main.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/23 下午4:52
 * @brief 计算机与程序设计笔记主页
 * @copyright CC BY-NC-SA 2024. All rights reserved.
 * */
#ifndef CBPD_MAIN_H
#define CBPD_MAIN_H
#pragma once

// 首页
/** @mainpage 计算机与程序设计笔记
 *
 * @tableofcontents
 *
 * @section intro 简介
 * 该笔记主要记录了董国良所著的 @e《计算机程序设计》 一书中的重要知识点,并且由于其与C语言编程的联系,
 * 笔者采用了以 @c Doxygen 格式编写,并从源码生成文档的方式写就此笔记.
 *
 * @section contents 目录
 *
 * @subpage chapter1
 *     - @ref ch1_1
 *     - @ref ch1_2
 *
 * @subpage chapter2
 *     - @ref ch2_1
 * */

// 第一章
/**
 * @page chapter1 第一章 程序设计与C语言
 *
 * @tableofcontents
 *
 * @section ch1_1 计算机与程序、程序设计语言
 *
 * @subsection ch1_1_1 程序设计语言
 * 1. 机器语言  \n
 * 由0、1二进制代码组成的能被机器直接理解、执行的指令集合。 @c 机器语言是计算机唯一能够直接执行的语言。
 *
 * 2. 汇编语言  \n
 * 汇编语言采用一定的助记符来替代机器语言中的指令和数据。
 * 将汇编语言源程序转换为等价的目标程序的过程称为汇编。
 * <span style="color: red">我们把机器语言和汇编语言统称为低级语言。</span>
 * @dot
 * digraph G {
 *     rankdir=LR;
 *     node [shape=box fontname=FangSong];
 *     B [label="汇编语言源程序"];
 *     C [label="汇编程序"];
 *     D [label="机器语言程序"];
 *     N [shape=point];
 *     B -> N;
 *     C -> N;
 *     N -> D;
 * }
 * @enddot
 *
 * 3. 高级语言   \n
 * 翻译程序有两种工作方式:解释方式和编译方式。
 *     * 解释:  \n
 *          解释程序对源程序是一边翻译一边执行,不产生目标程序.
 *     * 编译:  \n
 *          将高级语言所编写的源程序翻译成等价的用机器语言表示的目标程序.
 *
 * @dot
 * digraph G {
 *     rankdir=LR;
 *     node [shape=box fontname=FangSong];
 *     subgraph cluster_1 {
 *         label="解释方式";
 *         fontname=FangSong;
 *         A1 [label="高级语言源程序"];
 *         B1 [label="解释程序"];
 *         C1 [label="数据" shape=plaintext];
 *         D1 [label="计算结果" shape=plaintext];
 *         N1 [shape=point];
 *         N2 [shape=point];
 *         A1 -> N1;
 *         B1 -> N1;
 *         N1 -> N2;
 *         C1 -> N2;
 *         N2 -> D1;
 *     }
 *     subgraph cluster_2 {
 *         label="编译方式";
 *         fontname=FangSong;
 *         A2 [label="源程序"];
 *         B2 [label="编译程序"];
 *         C2 [label="目标程序.OBJ"]
 *         D2 [label="链接程序"];
 *         E2 [label="可执行程序.EXE"];
 *         F2 [label="数据" shape=plaintext];
 *         G2 [label="计算结果" shape=plaintext];
 *         N3 [shape=point];
 *         N4 [shape=point];
 *         N5 [shape=point];
 *
 *         A2 -> N3;
 *         B2 -> N3;
 *         N3 -> C2;
 *         C2 -> N4;
 *         D2 -> N4;
 *         N4 -> E2;
 *         E2 -> N5;
 *         F2 -> N5;
 *         N5 -> G2;
 *     }
 * }
 * @enddot
 *
 * @subsection ch1_2 简单的C语言程序
 *
 * @$
 * 函数 \begin{cases}
 *          函数首部:包括函数名、函数类型、函数属性、函数参数名(形式参数名)、参数类型  \\\\
 *          函数体 \begin{cases}
 *                声明部分 \begin{cases}
 *                        定义在本函数中用到的变量,如int a,b; \\\\
 *                        声明在本函数中调用的函数,如int max(int x,int y)
 *                         \end{cases} \\\\
 *                 执行部分:指定在函数中的操作,包含若干个语句
 *                 \end{cases}
 *     \end{cases}
 * @$
 *
 * @subsection ch1_3 运行C语言程序的步骤与方法
 *
 * 没什么好说的- -!
 * */

// 第二章
/**
 * @page chapter2 第二章 数据的存储与运算
 *
 * @tableofcontents
 *
 * @section ch2_1 数据的存储和表现形式
 *
 * @subsection ch2_1_1 数据的存储单位和地址
 *
 * 1. 位(bit, b):  \n
 * 每一个二极管元件成为一个"二进制位",是计算机存储信息的最小单位。
 *
 * 2. 字节(byte, B):  \n
 * 计算机中,通常将8个二进制位作为一个字节,即1B=8b。是计算机存储信息的基本单位。
 *
 * 3. 地址:  \n
 * ...
 *
 * @subsection ch2_1_2 不同类型数据的存储方式
 * 1. 整数类型:  \n
 * 十进制整数7以二进制形式用1字节进行存储时,存储单元如下:
 *
 * @$
 * \overbrace{\boxed{0}}^{符号位} \overbrace{\boxed{0} \boxed{0} \boxed{0} \boxed{0} \boxed{1} \boxed{1} \boxed{1}}^{数值}
 * @$
 *
 * 最高位(左边第一位)定义为符号位,0表示正数,1表示负数。此时能存储的数值范围为0~127。
 * 现在的C语言系统用4个字节表示一个整数,则可以存储的数值范围为-2147483648~2147483647。
 *
 * @remark 对于整数类型,在计算机中,整数的表示方式是补码形式。
 * 先将此数写成二进制形式,再取反,再加1,得到补码。
 * 1. 9的原码:  \n
 *     @p 00001001
 *
 * 2. 按位取反:  \n
 *     @p 11110110
 *
 * 3. 求补码:  \n
 *     @p 00001001
 *
 * @note 正数的补码与原码、反码相同
 * */

#endif  // CBPD_MAIN_H
