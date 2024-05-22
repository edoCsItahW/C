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
 * @Date: 2024/05/17 上午9:54
 * @Commend: define the basic function of array and its struct
 ******************************************************/
#pragma once

#ifndef EXPORT
#define EXPORT

#ifdef ALLOW_EXPORT
#define EXPORT_API __declspec(dllexport)

#else
#define EXPORT_API __declspec(dllimport)

#endif
#include "../libBuild/type.h"

/** 定义数组结构体
 *
 * @brief 该数组结构体可以存储任意类型的数组，包括整数数组、字符串数组等。其原理为将每个元素的指针都转换为空指针.
 *
 * @data len 数组长度
 * @data data 数组元素指针数组
 * @data type 数组元素类型
 * */
typedef struct {
	int len;   // the length of the array
	void **data;  // the pointer to the array
	Type type;  // the type of the array
} Array;

EXPORT_API Array *createArr_(int len, Type type, ...);

#define createArr(len, first, ...) createArr_(len, getType(first), first, ##__VA_ARGS__)  // 创建数组

EXPORT_API Array* createByRepeat_(int len, Type type, void* data);

#define createByRepeat(len, value) createByRepeat_(len, getType(value), value)  // 创建全为知道值的数组

typedef struct {
	Array* (*converInt)(int data[], int len);  // 将整数数组转换为数组结构体
	Array* (*convertString)(char *data[], int len);  // 将字符串数组转换为数组结构体
	void (*destroy)(Array *arr);  // 销毁数组
	void (*remove)(Array* arr, int idx);  // 从数组中移除元素
	void (*append)(Array* arr, void* data);  // 向数组中追加元素
	void (*print)(Array* arr);  // 打印数组
	Array* (*concat)(Array* arr1, Array* arr2);  // 拼接数组
	Array* (*range)(int start, int end);  // 数组切片
	void (*exclude)(Array arr, void *data);  // 数组元素去重
} S_arrMethod;

EXPORT_API S_arrMethod Arr;

#endif





