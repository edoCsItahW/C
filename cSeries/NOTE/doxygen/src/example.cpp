// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file example.cpp
 * @author: edocsitahw
 * @version: 1.1
 * @date: 2024/09/27 下午12:11
 * @brief: 这是实现example.h中定义的函数的源文件
 */

/**
 * @page page2 页面2的描述
 * @section section2 这是section2的描述
 * */

/**
 * @module example
 * @brief 这是example模块的描述
 * */
export module example;

#include "example.h"

/// @var g_exampleGlobalVar 全局变量的声明
extern int g_exampleGlobalVar;

/**
 * @brief 这是exampleFunction的描述
 * @var g_exampleGlobalVar 全局变量的声明
 * @invariant g_exampleGlobalVar >= 0
 * */
extern const int g_exampleGlobalConst;

/**
 * @test testExampleFunction 测试exampleFunction的功能
 * @throw 无
 * @todo 进行实现
 * @error Error 102: 无
 * */
int exampleFunction(int a, int b) {
    return a + b;
}
