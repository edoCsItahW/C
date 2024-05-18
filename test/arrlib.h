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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perarrlib.h"

// *********** 定义数组结构体 ***********

/** 定义数组结构体
 *
 * @brief 该数组结构体可以存储任意类型的数组，包括整数数组、字符串数组等。其原理为将每个元素的指针都转换为空指针.
 *
 * @data len 数组长度
 * @data data 数组元素指针数组
 * @data type 数组元素类型
 * */
typedef struct {
	int len;
	void **data;
	Type type;
} Array;

// *********** 实现数组结构体所具有方法 ***********

/** 创建数组
 *
 * @param data 数组元素指针数组
 * @param len 数组长度
 * @param type 数组元素类型
 * @return 数组结构体
 * */
Array createArr(void *data[], int len, Type type) {

	Array arr = {len, (void **)malloc(len * sizeof(void *)), type};

	if (arr.data == NULL)
		exit(EXIT_FAILURE);

	for (int i = 0; i < len; i++) {
		arr.data[i] = data[i];
	}

	return arr;

}

/** 将整数数组转换为数组结构体
 *
 * @param data 整数数组
 * @param len 数组长度
 * @return 数组结构体
 * */
Array convertInt(int data[], int len) {
	void **arr = (void **)malloc(len * sizeof(void *));

	if (arr == NULL) exit(EXIT_FAILURE);

	for (int i = 0; i < len; i++) {
		arr[i] = (void *)(data + i);
	}

	Array arrInt = {len, arr, Int};

	return arrInt;

}

/** 将字符串数组转换为数组结构体
 *
 * @param data 字符串数组
 * @param len 数组长度
 * @return 数组结构体
 * */
Array convertString(char *data[], int len) {
	void **arr = (void **)malloc(len * sizeof(void *));

	if (arr == NULL) exit(EXIT_FAILURE);

	for (int i = 0; i < len; i++)
	{
		arr[i] = (void *)(data + i);
	}

	Array arrString = {len, arr, String};

	return arrString;
}

/** 创建全为知道值的数组
 *
 * @param data 数组元素指针
 * @param len 数组长度
 * @return 数组结构体
 * */
Array createByRepeat(void *data, int len) {

	Array arr = {len, (void **) malloc(len * sizeof(void *))};

	if (arr.data == NULL) exit(EXIT_FAILURE);

	for (int i = 0; i < len; i++)
	{
		arr.data[i] = data;
	}

	return arr;

}

/** 打印数组
 *
 * @param arr 数组结构体
 * */
void print(Array arr) {

	printf("[");

	printMethod* method = printType(arr.type);

	for (int i = 0; i < arr.len; i++) {
		method->pMethod(arr.data[i], i, arr.len);
	}

	printf("]\n");

	free(method);
}

/** 拼接数组
 *
 * @param arr1 数组结构体1
 * @param arr2 数组结构体2
 * @return 数组结构体
 * */
Array concat(Array arr1, Array arr2) {

}

/** 排除数组中的指定元素
 *
 * @param arr 数组结构体
 * @param data 指定元素
 * @return 数组结构体
 * */
Array exclude(Array arr, void *data) {

}

// *********** 包装了数组结构体所具有方法的结构体 ***********

/** 定义数组方法结构体
 *
 * @data create 创建数组
 * @data createByRepeat 创建全为重复值的数组
 * @data convertInt 将整数数组转换为数组结构体
 * @data convertString 将字符串数组转换为数组结构体
 * @data concat 拼接数组
 * @data exclude 排除数组中的指定元素
 * */
typedef struct {
	Array (*create)(void **data, int len, Type type);   // 创建数组
	Array (*createByRepeat)(void *data, int len);  // 创建全为重复值的数组
	Array (*convertInt)(int data[], int len);  // 将整数数组转换为数组结构体
	Array (*convertString)(char *data[], int len);  // 将字符串数组转换为数组结构体
	void (*print)(Array arr);  // 打印数组
	Array (*concat)(Array arr1, Array arr2);  // 拼接数组
	Array (*exclude)(Array arr, void *data);  // 排除数组中的指定元素
} SarrMethod;

// *********** 定义数组方法结构体的实例 ***********

SarrMethod Arr = {
	.create = createArr,   // 创建数组
	.createByRepeat = createByRepeat,  // 创建全为重复值的数组
	.convertInt = convertInt,  // 将整数数组转换为数组结构体
	.convertString = convertString,  // 将字符串数组转换为数组结构体
	.print = print,  // 打印数组
	.concat = concat,  // 拼接数组
	.exclude = exclude  // 排除数组中的指定元素
};
