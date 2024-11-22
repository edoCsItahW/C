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
 *     - @ref ch1_3
 *
 * @subpage chapter2
 *     - @ref ch2_1
 *
 * @subpage chapter10
 *     - @ref ch10_1
 *     - @ref ch10_2
 *     - @ref ch10_3
 *     - @ref ch10_4
 *
 * @subpage chapter11
 *     - @ref ch11_1
 *     - @ref ch11_2
 *
 * @subpage chapter12
 *     - @ref ch12_1
 *     - @ref ch12_2
 *     - @ref ch12_3
 *     - @ref ch12_4
 *
 * @subpage chapter13
 *     - @ref ch13_1
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
 *
 * @subsubsection ch1_1_1_1 1. 机器语言
 * 由0、1二进制代码组成的能被机器直接理解、执行的指令集合。 @c 机器语言是计算机唯一能够直接执行的语言。
 *
 * @subsubsection ch1_1_1_2 2. 汇编语言
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
 * @subsubsection ch1_1_1_3 3. 高级语言
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
 *　@subsubsection　ch2_1_1_1_1 1. 位(bit, b):
 * 每一个二极管元件成为一个"二进制位",是计算机存储信息的最小单位。
 *
 * @subsubsection ch2_1_1_1_2 2. 字节(byte, B):
 * 计算机中,通常将8个二进制位作为一个字节,即1B=8b。是计算机存储信息的基本单位。
 *
 * @subsubsection ch2_1_1_1_3 3. 地址:
 * ...
 *
 * @subsection ch2_1_2 不同类型数据的存储方式
 *
 * @subsubsection ch2_1_2_1 1. 整数类型:
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

// 第十章
/**
 * @page chapter10 第十章 利用文件保存数据
 *
 * @tableofcontents
 *
 * @section ch10_1 C文件的有关概念
 *
 * @subsection ch10_1_1 文件和文件名
 *
 * @subsubsection ch10_1_1_1 1. 文件:
 *     在C语言程序设计中,主要有两种文件:
 *
 *     1. **程序文件**: 包括源程序文件(.c),目标文件(.obj),可执行文件(.exe)等。
 *     2. **数据文件**: 文件内容不是程序,而是供程序运行时读写的数据。
 *
 *     输入输出数据流的开始和结束仅受程序控制而不受物理符合(如回车换行)控制,这种文件称为@b 流式文件
 *
 * @subsubsection ch10_1_1_2 2. 文件名:  \n
 *     一个文件要有一个唯一的文件标识.文件名包括:(1)文件路径,(2)文件名主干,(3)文件扩展名。
 *
 * @subsubsection ch10_1_1_3 3. 数据文件的分类:  \n
 *
 *     根据数据的组织形式,数据文件可分为@b ASCII文件 和@b 二进制文件 .
 *
 *     ASCII文件又称@b 文本文件 ,每一个字节放一个字符的ASCII编码.
 *
 * @subsection ch10_1_2 文件缓冲区
 *
 * @dot
 * digraph G {
 *     rankdir=LR;
 *     node [shape=box fontname=FangSong];
 *
 *     subgraph cluster_1 {
 *         label="缓冲文件系统"
 *         fontname=FangSong;
 *
 *         A [label="程序数据区"];
 *         B [label="输出文件缓冲区"];
 *         C [label="输入文件缓冲区"];
 *
 *         A -> B [label="输出" fontname=FangSong];
 *         A -> C [label="输入" fontname=FangSong];
 *     }
 *
 *     D [label="磁盘"];
 *     B -> D [label="输出" fontname=FangSong];
 *     C -> D [label="输入" fontname=FangSong];
 * }
 * @enddot
 *
 * @subsection ch10_1_3 文件类型指针
 *
 * @section ch10_2 文件的打开与关闭
 *
 * @subsection ch10_2_1 打开数据文件
 *
 * "打开"是指为文件建立相应的信息区(用来存放有关文件的信息)和文件缓冲区(用来暂时存放输入输出的数据).
 *
 * <span style="color: red">用标准输入输出函数fopen()来实现打开文件.</span>
 *
 * @b fopen(文件名, 使用文件方式)
 *
 * 例如:
 * @code
 * FILE *fp;
 * fp = fopen("data.txt", "r");
 * @endcode
 *
 * 这样， @c fp 就和文件 "data.txt" 相关联了,或者说 @c fp 指向了 "data.txt" 的文件描述符.
 *
 * @subsection ch10_2_2 关闭数据文件
 *
 * "关闭"就是撤销文件信息区和文件缓冲区,使文件指针变量不再指向该文件.<span style="color: red">关闭文件用fclose()</span>.
 *
 * @b fclose(文件指针)
 *
 * 例如:
 * @code
 * fclose(fp);
 * @endcode
 *
 * fclose函数会返回一个值,当成功关闭文件时,返回0,否则返回 EOF(End Of File)(-1).如果不关闭文件将会丢失数据.
 *
 * @section ch10_3 顺序读写数据文件
 *
 * @subsection ch10_3_1 向文件读写字符串
 *
 * | 函数名 | 调用形式 | 功能 | 返回值 |
 * | ----- | ------ | --- | ----- |
 * | fgetc | fgetc(fp) | 从 fp 指向的文件读入一个字符 | 读入成功返回该字符,读入失败返回 EOF |
 * | fputc | fputc(ch, fp) | 把字符ch写入fp指向的文件 | 写入成功返回该字符,写入失败返回 EOF |
 *
 * 在访问磁盘文件时,是逐个字节进行的.系统用"文件读写位置标记"来表示当前所访问的位置.
 *
 * 可以用 @c feof() 函数来判断是否到达文件末尾.
 *
 * @subsection ch10_3_2 向文件读写字符串
 *
 * C语言运行通过函数@c fgets() 和@c fputs() 来实现读写字符串.
 *
 * | 函数名 | 调用形式 | 功能 | 返回值 |
 * | ----- | ------ | --- | ----- |
 * | fgets | fgets(str, n, fp) | 从 fp 指向的文件读入一个长度为(n-1)的字符串 | 读入成功返回字符串,读入失败返回 NULL |
 * | fputs | fputs(str, fp) | 把字符串str写入fp指向的文件 | 写入成功返回0,写入失败返回 EOF |
 *
 * @subsection ch10_3_3 文件的格式化读写
 *
 * 对文件进行格式化读写需要用到@c fprintf() 和@c fscanf() 函数.
 *
 * @c fprintf(文件指针, 格式字符串, 实参表...);
 * @c fscanf(文件指针, 格式字符串, 指针表...);
 *
 * @subsection ch10_3_4 二进制方式读写文件
 *
 * @c fwrite(buffer, size, count, fp) 和@c fread(buffer, size, count, fp) 函数可以实现二进制方式读写文件.
 * 其中 @b buffer 是一个地址, @b size 是每个数据项的字节数, @b count 是要读写的数据项个数, @b fp 是文件指针.
 *
 * <u>如果fread()或fwirte()函数执行成功,则返回实际读写的字节数,如果发生错误,则返回EOF.</u>
 *
 * @section ch10_4 文件的随机读写
 *
 * @subsection ch10_4_1 文件位置标记及其定位
 *
 * 1. @b 文件位置标记:  \n
 *     为了对读写进行控制,系统为每个文件都设置了一个 @b 文件读写位置标记 用来指示当前读写位置.
 *
 * 2. @b 文件位置标记的定位:  \n
 *     可以用 @c rewind() 函数来将文件读写位置标记定位到文件头,用 @c fseek(文件类型指针, 偏移量, 位置) 函数来将文件读写位置标记定位到指定位置.
 *     | 起始点 | 名字 | 用数字代替 |
 *     | ----- | --- | -------- |
 *     | 头 | SEEK_SET | 0 |
 *     | 当前位置 | SEEK_CUR | 1 |
 *     | 尾 | SEEK_END | 2 |
 * */

// 第十一章
/**
 * @page chapter11 第十一章 数据结构绪论
 *
 * @tableofcontents
 *
 * @section ch11_1 数据结构的基本概念
 *
 * @subsection ch11_1_1 常用术语
 *
 * @subsubsection ch11_1_1_1 1. 数据
 *     数据(Data)是客观事物的符号表示,是所有能输入计算机中并被计算机程序处理的对象.
 *
 * @subsubsection ch11_1_1_2 2. 数据元素
 *     数据元素(Data Element)是数据的基本单位,有时也称为元素、记录等.
 *
 * @subsubsection ch11_1_1_3 3. 数据项
 *     数据项(Data Item)是组成数据元素的、有独立含义的、不可分割的最小单位。
 *
 * @subsubsection ch11_1_1_4 4. 数据对象
 *     数据对象(Data Object)是具有相同性质的数据元素的集合,是数据的一个子集.
 *
 * @subsection ch11_1_2 数据结构
 *
 * @b 数据结构(Data Structure) 是相互之间存在一种或多种关系的数据元素的集合，"结构"指数据元素之间的关系.
 * 数据结构包括@b 逻辑结构 和 @b 存储结构.  \n
 *
 * @$
 * 数据结构 \begin{cases}
 *     逻辑结构 \begin{cases}
 *         线性结构  \\\\
 *         非线性结构
 *     \end{cases}  \\\\
 *     存储结构 \begin{cases}
 *         顺序存储结构  \\\\
 *         链式存储结构
 *     \end{cases}
 * \end{cases}
 * @$  \n
 *
 * @subsubsection ch11_1_2_1 1. 逻辑结构
 *     逻辑结构是从逻辑上描述数据结构,它与数据的存储无关,是独立于计算机的.
 *
 *     其包括:
 *     - 集合结构:  \n
 *         集合结构(Collection Structure)是指数据元素的集合,除了"属于同一集合"的关系外,别无其他关系.
 *     - 线性结构:  \n
 *         线性结构(Linear Structure)是指数据元素的有序序列,其中的元素之间存在一对一关系.
 *     - 树形结构:  \n
 *         树形结构(Tree Structure),数据元素之间存在一对多的关系.
 *     - 图状结构或网状结构:  \n
 *         图状结构(Graph Structure)或网状结构(Network Structure),数据元素之间存在多对多的关系.
 *
 *     线性结构包括线性表、栈、队列、字符串、数组、广义表等.
 *     非线性结构包括树、二叉树、有向图和无向图等.
 *
 * @subsubsection ch11_1_2_2 2. 存储结构
 *     数据对象在计算机中的存储方式称为 @b 存储结构 ,也称为 @b 物理结构.
 *     数据元素在计算机中有两种存储结构:
 *     - 顺序存储结构:  \n
 *         顺序存储结构(Sequential Storage Structure)是借助元素在存储器中的相对位置来表示元素之间的逻辑关系,通常借助程序设计语言中的数组实现.其要求所有的元素依次存储在一片连续的存储空间中.
 *     - 链式存储结构:  \n
 *         链式存储结构(Linked Storage Structure)是指数据元素在内存或磁盘上不连续分布的存储方式,通常借助于程序设计中的指针实现.
 * @section ch11_2 数据类型和抽象数据类型
 *
 * @subsection ch11_2_1 基本数据类型
 *
 * @subsubsection ch11_2_1_1 1. 数据类型
 *     在程序设计语言中,每一个数据都属于某种数据类型。类型明显或隐含地规定了数据的取值范围、存储方式以及允许进行的运算,@b 数据类型 是一个值的集合和定义在这个集合上的一组操作的总称.
 *
 * @subsubsection ch11_2_1_2 2. 抽象数据类型:
 *     抽象数据类型(Abstract Data Type, ADT)一般指由用户定义的、表示应用问题的数学模型,以及定义在该模型上的一组操作的总称,具体包括3个部分: 数据对象,数据对象上的关系的集合又及对数据对象的基本操作的集合.
 *
 * @subsection ch11_2_2 抽象数据类型的实现
 *
 * 略.
 * */

// 第十二章
/**
 * @page chapter12 第十二章 线性表
 *
 * @tableofcontents
 *
 * @section ch12_1 线性表的逻辑结构
 *
 * @subsection ch12_1_1 线性表的逻辑定义
 *
 * 线性表,或称表,是一种非常灵便的结构,可以根据需要改变表的长度,也可以在表中任何位置对元素进行访问、插入或删除等操作.
 *
 * <u>由特性相同的元素构成的有限序列称为线性表.线性表中元素的个数n(\$ \underline{ n \geqslant 0 } \$)定义为线性表的长度.n = 0 时,称为空表.</u>
 *
 * 对于线性表或线性结构,其特点是:
 * - 存在唯一的一个被称作@c 第一个 的数据元素;
 * - 存在唯一的一个被称作@c 最后一个 的数据元素;
 * - 除第一个数据元素之外,结构中的每个数据元素均只有一个前驱;
 * - 除最后一个元素之外,结构中的每个数据均只有一个后继;
 *
 * @subsection ch12_1_2 线性表的基本运算
 *
 * @c InitList(&L) 初始化一个空表@b L ,即表的在初始化.  \n
 * @c ListLength(L) 返回表@b L 的长度.  \n
 * @c GetElem(L, i, &e) 用e返回@c L 中第i个数据元素的值,\$ 1 \leqslant i \leqslant ListLength(L) \$.  \n
 * @c LocateElem(L, e) 返回@c L 中第1个值与e相同的元素的位置在@c L 中的位置,若不存在,则返回值为0.  \n
 * @c ListInsert(&L, i, e) 在@c L 中第i个位置之前插入新的元素e,@c L 的长度加1.  \n
 * @c ListDelete(&L, i) 删除@c L 中第i个数据元素,@c L 的长度减1.  \n
 *
 * @section ch12_2 线性表的顺序存储结构
 *
 * @subsection ch12_2_1 顺序表定义及地址计算
 *
 * @subsubsection ch12_1_1_1 1. 顺序表的定义
 *     线性表的顺序表示指的是用一组地址连续的存储单元依次存储线性表的数据元素,这种表示也称为线性表的顺序存储结构.
 *
 * @subsubsection ch12_1_1_2 2. 地址的计算方法
 * 假设线性表的每个元素需要占用l个存储单元,并以所占的第一个单元的存储地址作为数据元素的存储起始位置.则线性表中第i + 1个数据元素的存储位置\$ LOC(a_{i + 1}) \$ 和第i个数据元素的位置\$ LOC(a_i) \$之间满足下列关系:  \n
 *     @$
 *     LOC(a_{i + 1}) = LOC(a_i) + l
 *     @$  \n
 *
 * 一般来说,线性表的第i个数据元素@$ a_i @$的存储位置为:  \n
 *     @$
 *     LOC(a_i) = LOC(a_1) + (i - 1) l
 *     @$  \n
 *
 * @$
 * \begin{array}{lll}
 *     & b & \boxed{a_1} & 1 \\\\
 *     & b + 1 & \boxed{a_2} & 2 \\\\
 *     & \vdots & \boxed{\vdots} & \vdots \\\\
 *     & b + (n - 1) l & \boxed{a_i} & i  \\\\
 *     & \vdots & \boxed{\vdots} & \vdots \\\\
 *     & b + (n - 1) l & \boxed{a_n} & n
 * \end{array}
 * @$  \n
 *
 * @subsubsection ch12_1_1_3 3. 顺序表类型定义
 * 通常用数组来描述数据结构中的顺序存储结构.
 * @code{c}
 * // -------------- 顺序表的存储结构 ----------------
 *
 * #define MAXSIZE 100  // 顺序表可能达到的最大长度
 * typedef struct {
 *     ElemType *elem;  // 存储空间的基地址
 *     int length;      // 当前长度
 * }
 * @endcode
 *
 * @subsection ch12_2_2 顺序表的基本操作
 *
 * @subsubsection ch12_2_2_1 1. 初始化
 *     顺序表的初始化操作就是构造一个空的顺序表
 *
 *     @code{c}
 *     Status InitList(SqList *L) {  // 构造一个空的顺序表
 *         L.elem = new ElemType[MAXSIZE];  // 为顺序表分配存储空间
 *         if (!L.elem) exit(OVERFLOW);  // 存储分配失败退出
 *         L.length = 0;  // 空表的长度为0
 *         return OK;
 *     }
 *     @endcode
 *
 * @subsubsection ch12_2_2_2 2. 取值
 *     取值操作是根据指定的位置序号i,获取顺序表中的第i个数据元素的值.
 *
 *     @code{c}
 *     Status GetELem(SqList L, int i, ElemType &e) {
 *         if (i < 1 || i > L.length) return ERROR;  // 位置序号不合法
 *         e = L.elem[i - 1];  // elem[i - 1]单元存储第i个数据元素
 *         return OK;
 *     }
 *     @endcode
 *
 *     且显然,取值操作的时间复杂度为O(1).
 *
 * @subsubsection ch12_2_2_3 3. 查找
 *     查找操作是根据指定的元素e,查找顺序表中第1个与e相等的元素。若查找成功,则返回该元素在表中的位置序号;若查找失败则返回0.
 *
 *     @code{c}
 *     int LocateElem(SqList L, ElemType e) {
 *         for (i = 0; i < L.length; i++)
 *             if (L.elem[i] == e) return i + 1;  // 查找成功,返回序号i + 1
 *             return 0;  // 查找失败返回0
 *     }
 *     @endcode
 *
 *     - 当在查找一个元素时,其时间主要耗费在数据的比较上,而比较的次数取决于被查元素在列表中的位置.
 *     - 在查找时,为确定元素在顺序表中的位置,须和给定值进行比较的数据元素的个数的期望值称为查找算法在查找成功时的@c 平均查找长度(ASL) .
 *
 *     假设\$ P_i \$是查找第i个元素的概率,\$ C_i \$为找到表中的关键字于给定值相等的第i个记录时,和给定值已进行过的比较的关键字的个数.
 *     假设每个元素的查找概率相等,即\$ P_i = 1/n \$ ,则有:  \n
 *
 *     @$ \displaystyle
 *     ASL = \sum_{i = 1}^n p_i C_i = \frac{1}{n} \sum_{i = 1}^n i = \frac{n + 1}{2}
 *     @$  \n
 *
 *     由此可见,顺序表按值查找的平均时间复杂度为O(n).
 *
 * @subsubsection ch12_2_2_4 4. 插入
 *     线性表的插入操作时指在表的第i(\$ 1 \leqslant i \leqslant n+1 \$)个位置插入一个新的元素e,使长度为n的线性表变为长度为n + 1的线性表.
 *
 *     @code{c}
 *     Status ListInsert(SqList *L, int i, ELemType e) {
 *         if ((i < 1) || (i > L.length + 1)) return ERROR;  // i值不合法
 *         if (L.length == MAXSIZE) return ERROR;  // 表以满,不能插入
 *         for (j = L.length; j >= i - 1; i--) L.elem[j + 1] = L.elem[j];  // 后移元素
 *         L.elem[i - 1] = e;  // 插入新元素
 *         ++L.length;  // 表长度加1
 *         return OK;
 *     }
 *     @endcode
 *
 *     假设\$ E_{ins} \$为在长度为n的线性表中插入一个元素时所需的移动元素的期望值,假定在线性表的任何位置上插入元素都是概率的,即:  \n
 *     @$
 *         p_i = \frac{1}{n + 1}
 *     @$  \n
 *
 *     则:  \n
 *
 *     @$
 *         E_{ins} = \displaystyle \sum_{i = 1}^{n + 1} p_i (n - i + 1) = \frac{1}{n + 1} \sum_{i = 1}^{n + 1} (n - i + 1) = \frac{n}{2}
 *     @$
 *
 *     由此可见,顺序表的插入算法的平均时间复杂度为O(n).
 *
 * @subsubsection ch12_2_2_5 5. 删除
 *     线性表的删除操作是指将表的第i个元素删去,将长度为n - 1的线性表.
 *
 *     @code{c}
 *     Status ListDelete(SqList *L, int i) {
 *         if ((i < 1) || (i > L.length)) return ERROR;  // i值不合法
 *         for (j = i; j <- L.length; i++) L.elem[j - 1] = L.elem[j];  // 前移元素
 *         --L.length;  // 表长度减1
 *         return OK;
 *     }
 *     @endcode
 *
 *     假设\$ E_{del} \$为在长度为n的线性表中删除一个元素时所需的移动元素的期望值,假定在线性表的任何位置上删除元素都是概率的,即:  \n
 *     @$
 *         p_i = \frac{1}{n}
 *     @$  \n
 *
 *     则:  \n
 *     @$
 *         E_{del} = \displaystyle \sum_{i = 1}^{n - 1} p_i (n - i) = \frac{1}{n} \sum_{i = 1}^{n - 1} (n - i) = \frac{n - 1}{2}
 *     @$
 *
 *     由此可见,顺序表的删除算法的平均时间复杂度为O(n).
 *
 * @section ch12_3 线性表的链式存储结构
 *
 * @subsection ch12_3_1 单链表
 *
 * @subsubsection ch12_3_1_1 1. 单链表的定义与表示
 *
 * n个结点链接成一个链表即为线性表的链式存储结构.线性表的存储结构的特点是:用一组任意的存储单元存储线性表的数据元素,这组存储单元可以是连续的,也可以是离散的.单链表的节点可以包括两个域: 数据域用于存储数据元素;指针域用于存储直接后继的存储位置,指针域中存储的信息称作指针或链,单链表的每个结点中只包含一个指针域.
 *
 * @b 头结点 :  \n
 * 链表添加头结点的作用:  \n
 *     - 便于首元结点处理
 *     - 便于空表和非空表的统一处理
 *     增加头结点后,无论链表是否为空,头指针都是指向头结点的非空指针.
 *
 * @b 单链表的类型定义 :  \n
 * @code{c}
 * typedef struct Node {
 *     ElemType data;  // 数据域
 *     struct Node *next;  // 指针域
 * }
 * @endcode
 *
 * @subsubsection ch12_3_1_1 2. 单链表的基本操作
 *     1. 初始化:  \n
 *         1. 生成新的结点作为头结点,用头指针L指向头结点
 *         2. 头结点的指针域置空
 *         @code{c}
 *         Status InitList(LinkList *L) {
 *             L = new LNode;  // 生成新结点作为头结点
 *             L->next = NULL;  // 头结点的指针域置空
 *             return OK;
 *         }
 *         @endcode
 *
 *     2. 取值:  \n
 *         1. 用指针P指向首元结点,用j做计数器,初值赋1
 *         2. 从首元结点开始依次顺着链域next逐个结点向下访问,只要指向当前结点的指针p不为空(NULL),并且没有到达序号为i的结点,则循环执行以下操作:
 *             - p指向下一个结点
 *             - j加1
 *         3. ...
 *         @code{c}
 *         Status GetElem(LinkList L, int i, ELemType &e) {
 *             p = L->next;
 *             j = 1;
 *             while (p && j < i) {
 *                 p = p->next;
 *                 j++;
 *             }
 *             if (!p || j > i) return ERROR;  // 位置序号不合法
 *             e = p->data;  // 取值成功,返回数据元素
 *             return OK;
 *         }
 *         @endcode
 *         假设每个位置上元素的取值概率相等,即\$ P_i = 1/n \$ ,则有:  \n
 *         @$
 *         ASL = \frac{1}{n} \sum_{i = 1}^n (i - 1) = \frac{n - 1}{2}
 *         @$  \n
 *         由此可见,单链表按值查找的平均时间复杂度为O(n).
 *
 *     3. 查找:  \n
 *         1. 用指针P指向首元结点
 *         2. 从首元结点开始依次顺着链域next向下查找,只要指向当前结点的指针p不为空,并且p所指结点的数据域不等于给定值e,则循环执行操作:p指向下一个结点
 *         3. 返回p
 *         @code{c}
 *         LNode *LocateElem(LinkList L, ElemType e) {
 *             p = L->next;
 *             while (p && p->data != e) p = p->next;
 *             return p;  // 返回查找到的结点指针
 *         }
 *         @endcode
 *         复杂度也为O(n).
 *
 *     4. 插入:  \n
 *         1. 查找结点\$ a_{i - 1} \$并由指针p指向该结点
 *         2. 生成一个新结点*s
 *         3. 将新结点*s的数据域置为e
 *         4. 将新结点*s的指针域置为\$ a_{i} \$
 *         5. 将结点*p的指针域指向新结点*s
 *         @code{c}
 *         Status ListInsert(LinkList &L, int i, ElemType e) {
 *             p = L;
 *             j = 0;
 *             while (p && (j < i - 1)) {
 *                 p = p->next; ++j;
 *             }
 *             if (!p || j > i - 1) return ERROR;
 *             s = new LNode;
 *             s->data = e;
 *             s->next = p->next;
 *             p->next = s;
 *             return OK;
 *         }
 *         @endcode
 *     5. 删除:  \n
 *         1. 查找结点\$ a_{i - 1} \$并由指针p指向该结点
 *         2. 临时保存待删除结点\$ a_i \$的地址在q中,以备释放
 *         3. 将结点*p的指针域指向\$ a_i \$的直接后继结点\$ a_{i+1} \$
 *         4. 释放结点\$ a_i \$的空间
 *         @code{c}
 *         Status ListDelete(LinkList &L, int i) {
 *             p = L;
 *             j = 0;
 *             while ((p -> next) && (j < i - 1)) {
 *                p = p->next;
 *                ++j;
 *             }
 *             if (!(p->next) || (j > i - 1)) return ERROR;
 *             q = p->next;
 *             p->next = q->next;
 *             delete q;
 *             return OK;
 *         }
 *         @endcode
 *
 *     6. 创建单链表
 *         1. 前插法:  \n
 *             前插法是通过将新结点逐个插入链表的头部来创建链表,每次申请一个新结点,读入相应的数据元素值,然后将新结点插入到头结点之后.
 *
 *         2. 后插法:  \n
 *             后插法是通过将新结点逐个插入链表的尾部来创建链表.
 *
 * @subsection ch12_3_2 循环链表
 *
 * @subsubsection ch12_3_2_1 1. 单循环列表
 *
 * 将最后一个结点的指针域指向头结点,使得整个链表形成一个环,这种首尾相接的链表称为循环链表
 *
 * @subsubsection ch12_3_2_2 2. 双向链表
 *
 * 在链表的每个结点中设置两个指针,一个指向后继结点,另一个指向前驱结点
 *
 * @subsection ch12_3_3 顺序表和链表的比较
 *
 * @subsubsection ch12_3_3_1 1. 空间性能的比较
 *
 * 1. 存储空间的分配  \n
 *     顺序表的空间必须预先分配,元素个数受到一定限制,易造成存储空间浪费或空间溢出现象.<u>当线性表的长度变化较大,难以预估存储规模时,宜采用链表作为存储结构</u>
 *
 * 2. 存储密度大小  \n
 *     当线性表的长度变化不大,易于事先确定其大小时,为了节约存储空间,宜采用顺序表作为存储结构.
 *
 * @subsubsection ch12_3_3_2 2. 时间性能的比较
 *
 * 1. 存取元素的效率  \n
 *     若线性表的主要操作是和元素位置紧密相关的取值操作,很少做插入或删除时,宜采用顺序表作为存储结构.
 *
 * 2. 插入和删除操作效率  \n
 *     对于频繁进行插入或删除操作的线性表,宜采用链表作为存储结构
 *
 * @section ch12_4 线性表的应用
 *
 * @subsection ch12_4_1 线性表的合并
 *
 * 1. 分别获取LA表长m和LB表长n  \n
 * 2. 从LB中第一个数据元素开始,循环n次执行以下操作:  \n
 *     - 从LB中查找第i(\$ 1 \leqslant i \leqslant n \$)个数据元素赋给e
 *     - 在LA中查找元素e,如果不存在,则将e插在表LA的最后
 * @code{c}
 * void MergeList(List &LA, list LB) {
 *     m = ListLength(LA);
 *     n = ListLength(LB);
 *     for (i = 1; i <= n; i++) {
 *         GetElem(LB, i, e) {
 *             if (!LocateElem(LA, e)) ListInsert(LA, ++m, e);
 *         }
 *     }
 * }
 * @endcode
 * 顺序表和链表的合并算法的时间复杂度都是O(m x n)
 *
 * @subsection ch12_4_2 有序表的合并
 *
 * @subsubsection ch12_4_2_1 1. 顺序有序表的合并
 *
 * 若线性表中的数据元素可以相互比较,并且数据元素在线性表中依值非递减或非递增有序排列,则称该线性表为有序表.
 *
 * 1. 创建一个表长为m+n的空表LC
 * 2. 指针pc初始化,指向LC的第一个元素
 * 3. 指针pa和pb初始化,分别指向LA和LB的第一个元素
 * 4. 当指针pa和pb均未到达相应表尾时,则依次比较pa和pb所指向的元素值,从LA或LB中取元素较小的结点插入到LC的最后
 * 5. 如果pb已到达LB表尾,依次将LA的剩余元素插入到LC的最后
 * 6. 如果pa已到达LA表尾,依次将LB的剩余元素插入到LC的最后
 * @code{c}
 * void MergeList_Sq(SqList &LA, SqList LB, SqList &LC) {
 *     LC.length = LA.length + LB.length;
 *     LC.elem = new ElemType[LC.length];
 *     pc = LC.elem;
 *     pa = LA.elem;
 *     pa_last = LA.elem + LA.length - 1;
 *     pb_last = LB.elem + LB.length - 1;
 *     while ((pa <= pa_last) && (pb <= pb_last)) {
 *         if (*pa <= *pb) *pc++ = *pa++;
 *         else *pc++ = *pb++;
 *     }
 *     while (pa <= pa_last) *pc++ = *pa++;
 *     while (pb <= pb_last) *pc++ = *pb++;
 * }
 * @endcode
 * 算法循环最多执行m+n次,时间复杂度为O(m+n)
 *
 * @subsubsection ch12_4_2_2 2. 链式有序表的合并
 *
 * 1. 指针pa和pb初始化,分别指向LA和LB的第一个元素
 * 2. LC的结点取值为LA的头结点
 * 3. 指针pc初始化,指向LC的头结点
 * 4. 当指针pa和pb均未到达相应表尾时,则依次比较pa和pb所指向的元素值,从LA或LB中取元素较小的结点插入到LC的最后
 * 5. 将非空表的剩余部分插入到pc所指结点的后继结点
 * 6. 释放LB的头结点
 * @code{c}
 * void MergeList_L(LinkList &LA, LinkList LB, LinkList &LC) {
 *     pa = LA->next;
 *     pb = LB->next;
 *     LC = LA;
 *     pc = LC;
 *     while (pa && pb) {
 *         if (pa->data <= pb->data) {
 *             pc->next = pa;
 *             pc = pa;
 *             pa = pa->next;
 *         }
 *         else {
 *             pc->next = pb;
 *             pc = pb;
 *             pb = pb->next;
 *         }
 *     }
 *     pc->next = pa ? pa : pb;
 *     delete LB;
 * }
 * @endcode
 * */

// 第十三章
/**
 * @page chapter13 第十三章 栈和队列
 *
 * @tableofcontents
 *
 * @section ch13_1 栈
 *
 * @subsection ch13_1_1 栈的定义与特点
 *
 * 栈(stack)是限定仅在表尾进行插入或删除操作的线性表.因此,对栈来说,表尾端有其特殊含义,称为@b 栈顶 (top),相应地,表头端称为@b 栈底 (bottom).不含元素的栈称为空栈.
 *
 * <u>栈的修改是按@b 先进后出 (first-in-last-out) 的原则进行的</u>,即先进入栈的元素,最后离开栈.
 *
 * @subsection ch13_1_2 栈的基本操作
 *
 * 栈的基本运算除了有入栈和出栈外,还有栈的初始化,判空,栈顶元素的访问,栈的深度等操作.
 *
 * @c InitStack(&S) : 初始化操作,构造一个空栈
 * @c StackEmpty(S) : 判断栈是否为空.若栈为空,则返回1,否则返回0
 * @c Push(&S, x) : 入栈操作,将元素x压入栈S的顶端
 * @c Pop(&S, &x) : 出栈操作,将栈S的顶端元素弹出,并将其值赋给x
 * @c GetTop(S, &x) : 访问栈顶元素操作,将栈S的顶端元素的值赋给x,但不弹出
 *
 * @subsection ch13_1_3 顺序栈的表示和实现
 *
 * @subsubsection ch13_1_3_1 1. 顺序栈的表示
 * @code{c}
 * // ---------- 顺序栈的存储结构 ----------
 * #define MAXSIZE 100
 * typedef struct {
 *     SElemType *base;  // 栈底指针
 *     SElemType *top;   // 栈顶指针
 *     int stacksize;    // 栈的容量
 * } SqStack;
 *  @endcode
 *  base为栈底指针,初始化完成后,栈底指针base始终指向栈底的位置,若base的值为@c NULL ,则说明栈为空.
 *  top为栈顶指针,其初值指向栈底.每当插入新的栈顶元素时,指针top加1,删除栈顶元素时,指针top减1.因此,栈空时,top和base的值相等,都指向栈底;栈非空时,top始终指向栈顶元素的上一个位置.
 *
 *  @subsubsection ch13_1_3_2 2. 顺序栈的初始化
 *  1. 为顺序栈动态分配一个最大容量为MAXSIZE的数组空间,使base指向这段空间的基地址,即栈底.
 *  2. 栈顶指针top初始化为base,表示栈空
 *  3. stacksize置为栈的最大容量MAXSIZE
 *  @code{c}
 *  Status InitStack(SqStack &S) {
 *      S.base = new SElemType[MAXSIZE];
 *      if (!S.base) exit(OVERFLOW);
 *      S.top = S.base;
 *      S.stacksize = MAXSIZE;
 *      return OK;
 *  }
 *  @endcode
 *
 *  @subsubsection ch13_1_3_3 3. 入栈
 *
 *  入栈操作是指在栈顶插入一个新的元素
 *
 *  1. 判断栈是否满,若满则返回ERROR
 *  2. 将新元素压入栈顶,栈顶指针加1
 *
 *  @code{c}
 *  Status Push(SqStack &S, SElemType x) {
 *      if (S.top - S.base == S.stacksize) return ERROR;
 *      *S.top++ = x;
 *      return OK;
 *  }
 *  @endcode
 *
 * @subsubsection ch13_1_3_4 4. 出栈
 * 此操作是将栈顶元素删除
 * 1. 判断栈是否空,若空返回ERROR
 * 2. 栈顶指针减1,栈顶元素出栈
 *
 * @code{c}
 * Status Pop(SqStack &S, SElemType &x) {
 *     if (S.top == S.base) return ERROR;
 *     x = *--S.top;
 *     return OK;
 * }
 * @endcode
 *
 * @subsubsection ch13_1_3_5 5. 取栈顶元素
 * 当栈非空时,此操作返回当前栈顶元素的指,栈顶指针保持不变
 * @code{c}
 * SElemType GetTop(SqStack S) {
 *     if (S.top != S.base) return *(S.top - 1);
 * }
 * @endcode
 *
 * @subsection ch13_1_4 链栈的表示和实现
 *
 * @subsubsection ch13_1_4_1 1. 链栈的定义
 *
 * @code{c}
 * // ---------- 链栈的存储结构 ----------
 * typedef struct StackNode {
 *     ElemType data;
 *     struct StackNode *next;
 * } StackNode, *LinkStack;
 * @endcode
 *
 * @subsubsection ch13_1_4_2 2. 链栈的初始化
 *
 * 链栈的初始化操作就是构造一个空栈,直接将栈顶指针置空即可
 * @code{c}
 * Status InitStack(LinkStack &S) {
 *     S = NULL;
 *     return OK;
 * }
 * @endcode
 *
 * @subsubsection ch13_1_4_3 3. 入栈
 * 链栈入栈前不需要判断栈是否满,只需要为入栈元素动态分配一个结点空间.
 * 1. 为入栈元素x分配空间,用指针p指向
 * 2. 将新结点数据域置为x
 * 3. 将新结点插入栈顶
 * 4. 修改栈顶指针为p
 * @code{c}
 * Status Push(LinkStack &S, ElemType x) {
 *     p = new StackNode;
 *     p->data = x;
 *     p->next = S;
 *     S = p;
 *     return OK;
 * }
 * @endcode
 *
 * @subsubsection ch13_1_4_4 4. 出栈
 *
 * 链栈出栈前需要判断栈是否空,若空则返回ERROR.
 *
 * 1. 判断栈是否空,若空则返回ERROR
 * 2. 将栈顶赋值给x
 * 3. 临时保存栈顶元素的空间,以备释放
 * 4. 修改栈顶指针,指向新的栈顶元素
 * 5. 释放原栈顶元素的空间
 * @code{c}
 * Status Pop(LinkStack &S, ElemType &x) {
 *     if (S == NULL) return ERROR;
 *     x = S->data;
 *     p = S;
 *     S = S->next;
 *     delete p;
 *     return OK;
 * }
 * @endcode
 *
 * @subsubsection ch13_1_4_5 5. 取栈顶元素
 * @code{c}
 * SElemType GetTop(LinkStack S) {
 *     if (S != NULL) return S->data;
 * }
 * @endcode
 *
 * @section ch13_2 栈与递归
 *
 * @subsection ch13_2_1 采用递归算法解决问题
 *
 * @subsubsection ch13_2_1_1 1. 定义是递归的
 *
 * @$
 * Fact(n) = \begin{cases}
 *               1 & n = 0 \\\\
 *               n Fact(n - 1) & n > 0
 *           \end{cases}
 * @$
 *
 * 1. 能将一个问题转变为一个新问题,而新问题与原问题的解法相同或类同,不同的仅是处理对象,并且这些处理对象更小且变化有规律.
 * 2. 可以通过上述转化而使问题简化
 * 3. 必须有一个明确的递归出口,或称递归边界
 *
 * @code{c}
 * void p(参数表) {
 *     if (递归边界) 可直接求解;
 *     else p(较小的子问题);
 * }
 * @endcode
 *
 * @subsection ch13_2_2 递归算法的效率分析
 *
 * @subsubsection ch13_2_2_1 1. 时间复杂度分析
 *
 * @$
 * T(n) = \begin{cases}
 *            D & n = 0  \\\\
 *            C + T(n - 1) & n > 0
 *        \end{cases}
 * @$  \n
 *
 * 设n > 2,利用上式对T(n - 1)展开,即在上式中用n - 1代替n得到:  \n
 * @$
 *     T(n - 1) = C + T(n - 2)
 * @$
 *
 * 再代入\$ T(n) = C + T(n - 1) \$中,有:  \n
 * @$
 *     T(n) = 2C + T(n - 2)
 * @$
 *
 * 依次类推,当n > i时有:  \n
 * @$
 *     T(n) = iC + T(n - i)
 * @$
 *
 * 最后,当i = n时有:  \n
 * @$
 *     T(n) = nC + T(0) = nC + D
 * @$
 *
 * 则递归算法的时间复杂度为O(n)
 *
 * @section ch13_3 队列
 *
 * @subsection ch13_3_1 队列的定义与特点
 *
 * 队列是另一种特殊的线性表,只在表头进行删除操作,只在表尾进行插入操作.由于<u>队列的修改是按@b 先进先出 (first-in-first-out) 的原则进行的</u>,即先进入队列的元素,最先离开队列</u>
 *
 * @subsection ch13_3_2 队列的基本运算
 *
 * 
 * */
#endif  // CBPD_MAIN_H
