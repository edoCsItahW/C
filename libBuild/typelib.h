// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: test
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/05/18 下午9:29
 * @Commend:
 *******************************************************/
/** 类型定义
 *
 * @data value: 类型值
 * @data name: 类型名称
 * */
typedef struct {
	int value;
	char *name;
} Type;

Type Int = {1, "Int"};  // 定义Int类型
Type Float = {2, "Float"};  // 定义Float类型
Type Double = {3, "Double"};  // 定义Double类型
Type Char = {4, "Char"};  // 定义Char类型
Type Bool = {5, "Bool"};  // 定义Bool类型
Type String = {6, "String"};  // 定义String类型
Type Void = {7, "Void"};  // 定义Void类型
Type Array_ = {8, "Array"};  // 定义Array类型
Type Dict_ = {9, "Dict"};  // 定义Dict类型
