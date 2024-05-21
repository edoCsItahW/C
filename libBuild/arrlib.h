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
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typelib.h"

typedef void (*arrPrintFuncType)(void *, int, int);  // 打印函数类型

/** 定义打印函数结构体
 *
 * @data pFunc 打印函数指针
 * */
typedef struct {
	arrPrintFuncType pFunc;  // 打印函数指针
} arrPrintFunc;

static void arrPrintInt(void *data, int idx, int len) {  // 打印整数数组
	printf(idx == len - 1 ? "%d" : "%d, ", *(int *)data);
}

static void arrPrintString(void *data, int idx, int len) {  // 打印字符串数组
//	printf(idx == len - 1 ? "'%s'" : "'%s', ", *(char **)data);
	printf(idx == len - 1 ? "'%s'" : "'%s', ", (char *)data);
}

/** 打印数组元素
 *
 * @param type 数组元素类型
 * @return 打印函数指针
 * */
static arrPrintFunc * arrPrintType(const Type type) {
	arrPrintFunc * pFunc = (arrPrintFunc *)malloc(sizeof(arrPrintFunc));

	if (type.value == Int.value) {
		pFunc->pFunc = arrPrintInt;
	}
	else if (type.value == String.value) {
		pFunc->pFunc = arrPrintString;
	}
	else {
		printf("Error: unsupported type.\n");
		exit(EXIT_FAILURE);
	}

	return pFunc;
}

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
	int len;  // 数组长度
	void **data;  // 数组元素指针数组
	Type type;  // 数组元素类型
} Array;

/** 创建数组
 *
 * @param data 数组元素指针数组
 * @param len 数组长度
 * @param type 数组元素类型
 * @return 数组结构体
 * */
Array createArr(int len, Type type, ...) {

	va_list args;

	va_start(args, type);

	Array arr = {len, (void **)malloc(len * sizeof(void *)), type};

	if (arr.data == NULL)
		exit(EXIT_FAILURE);

	for (int i = 0; i < len; i++) {
		if (type.value == Int.value) {
			int *tmp = (int *)malloc(sizeof(int));  // va_arg(args, int);

			*tmp = va_arg(args, int);

			arr.data[i] = (void *)tmp;
		}
		else if (type.value == String.value) {
			char **tmp = (char **)malloc(sizeof(char *)); // va_arg(args, char **);

			*tmp = va_arg(args, char *);

			arr.data[i] = *(void **)tmp;
		}
		else {
			printf("Error: unsupported type.\n");

			exit(EXIT_FAILURE);

		}

	}

	va_end(args);

	return arr;

}

// *********** 实现数组结构体所具有方法 ***********

/** 将整数数组转换为数组结构体
 *
 * @param data 整数数组
 * @param len 数组长度
 * @return 数组结构体
 * */
static Array convertInt(int data[], int len) {
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
static Array convertString(char *data[], int len) {
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
static Array createByRepeat(int len, Type type, void *data) {

	Array arr = {len, (void **) malloc(len * sizeof(void *)), type};

	if (arr.data == NULL) exit(EXIT_FAILURE);

	for (int i = 0; i < len; i++){
		arr.data[i] = (void *)data;
	}

	return arr;

}

Array removeElem(Array arr, int idx) {
	if (idx < 0 || idx >= arr.len) {
		perror("Error: index out of range.\n");
		exit(EXIT_FAILURE);
	}

	Array newArr = {arr.len - 1, (void **)malloc((arr.len - 1) * sizeof(void *)), arr.type};

	if (newArr.data == NULL) exit(EXIT_FAILURE);

	int current = 0;

	for (int i = 0; i < arr.len; i++) {
		if (i != idx) {
			newArr.data[current] = arr.data[i];
			current++;
		}
	}

	return newArr;
}

void append(Array arr, void *data) {
	realloc(arr.data, (arr.len + 1) * sizeof(void));

	arr.data[arr.len] = data;
	arr.len++;
}

/** 打印数组
 *
 * @param arr 数组结构体
 * */
static void printArr(Array arr) {

	printf("[");

//	PrintMethod* method = chooseType(Array_);  // 返回一个指向PrintMethod结构体的指针
//
//	for (int i = 0; i < arr.len; i++) {
//		apMethod arrMethod = (apMethod)method->printType;  // 返回一个指向arrPrintMethod结构体的指针
//
//		arrPrintMethod* aMethod = arrMethod(arr.type);
//
//		ArrPrintMethod ArrMethod = (ArrPrintMethod)aMethod->printType;
//
//		ArrMethod(arr.data[i], i, arr.len);
//	}
	arrPrintFunc * pFunc = arrPrintType(arr.type);

	for (int i = 0; i < arr.len; i++) {
		pFunc->pFunc(arr.data[i], i, arr.len);
	}

	printf("]\n");

	free(pFunc);
}

/** 拼接数组
 *
 * @param arr1 数组结构体1
 * @param arr2 数组结构体2
 * @return 数组结构体
 * */
static Array concat(Array arr1, Array arr2) {
	Array arr = {arr1.len + arr2.len, (void **)malloc((arr1.len + arr2.len) * sizeof(void *)), arr1.type};

	for (int i = 0; i < arr1.len; i++) {
		arr.data[i] = arr1.data[i];
		arr.data[i + arr2.len] = arr2.data[i];
	}

	return arr;

}

Array range(int start, int end) {
	int len = end - start + 1;

	Array arr = {len, (void **)malloc(len * sizeof(void *)), Int};

	if (arr.data == NULL) exit(EXIT_FAILURE);

	for (int i = 0; i < len; i++) {
		int *tmp = (int *)malloc(sizeof(int));

		*tmp = start + i;

		arr.data[i] = (void*)tmp;
	}

	return arr;

}

/** 排除数组中的指定元素
 *
 * @param arr 数组结构体
 * @param data 指定元素
 * @return 数组结构体
 * */
static Array exclude(Array arr, void *data) {
	Array newArr;
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
	Array (*create)(int len, Type type, ...);   // 创建数组
	Array (*createByRepeat)(int len, Type type, void *data);  // 创建全为重复值的数组
	Array (*convertInt)(int data[], int len);  // 将整数数组转换为数组结构体
	Array (*convertString)(char *data[], int len);  // 将字符串数组转换为数组结构体
	Array (*remove)(Array arr, int idx);  // 移除数组中的元素
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
	.remove = removeElem,  // 移除数组中的元素
	.print = printArr,  // 打印数组
	.concat = concat,  // 拼接数组
	.exclude = exclude  // 排除数组中的指定元素
};
