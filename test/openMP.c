// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: C
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/05/29 下午3:31
 * @Commend:
 *******************************************************/

/**
 命令行中加入-omp选项，编译器会自动添加omp.h头文件，并将omp关键字识别为OpenMP关键字。
 #pragma omp 指导语句名 [子句, ...] 换行符
 子句:
     atomic: 定义一个必须被原子更新的内存区域
     barrier: 同步所有线程，直到所有线程都到达该语句
     critical: 定义一个临界区，同一时刻只能有一个线程执行
     flush: 同步指导语句,确保并行区域中的所有线程对内存中指定的对象有相同的取值
     for: 标明for循环中的迭代需要使用多个线程并行执行
     parallel: 定义一个由多个线程执行的并行代码区域,原线程成为主线程
     parallel do: 将循环迭代分配到多个线程
     parallel for: 类似于parallel do,但循环迭代的范围由用户指定

 编译指导语句:        子句:
     Parallel:
         Copying:
         default:
         firstprivate:
         private:
         shared:
         reduction:
     Section:
         firstprivate:
         Private:
         reduction:
         schedule:
         lastprivate:
     Sections:
         firstprivate:
         lastprivate:
         reduction:
         private:
     Critical:
         - 无
     Berrier:
         - 无
     Atomic:
         - 无
     Flush(List):
         - 无
     Ordered:
         - 无
     Threadadaptive:
         - 无

 default(模式): 控制变量默认的共享属性。模式可以是private,shared和none。
 shared(列表): 在parallel或者task编译指导语句产生的线程共享的列表条目,例如: #pragma omp parallel default(shared)
 copyin(列表): 将列表中列出的变量的值从主线程复制到工作线程
 num_threads(整数表达式): 设定线程数量

*/


/** CUDA C 语言拓展

 global void function(...): 定义在设备上运行的内核函数
 device int var: 存储在设备全局内存的变量
 shared int var: 存储在块共享内存中的变量
 local int var: 存储在块共享内存中的变量,只能在线程内使用
 constant int const: 存储在常数存储器中的常数

*/
