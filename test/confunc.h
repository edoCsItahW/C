// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// -------------------------<edocsitahw>----------------------------
// 传建时间: 2024/05/08 下午8:40
// 当前项目名: test
// 编码模式: utf-8
// 注释:
// -------------------------<edocsitahw>----------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXPORT

/** 检查内存是否分配成功。
 *
 * @param arr 整数数组结构体。
 * @return 0: 成功; 1: 失败。
 * */
int checkMemoryInt(const int* arr) {

	if (arr == NULL) {
		perror("Memory allocation failed!");
		return 1;
	}

	return 0;
}

int checkMemoryStr(const char** str) {
	if (str == NULL) {
		perror("Memory allocation failed!");
		return 1;
	}
	return 0;
}

/** 整数数组结构体。
 *
 * @data len: 数组长度。
 * @data data: 数组元素指针->数组。
 * */
typedef struct {
	int len;  // 数组长度
	int *data;  // 数组元素指针->数组
} IntArray;

/** 创建相同值的整数数组。
 *
 * @param len 数组长度。
 * @param num 数组元素值。
 * @return 整数数组结构体。
 * */
IntArray createIntCA(int len, int num) {
	IntArray arr = {len, (int*)malloc(len * sizeof(int))};

	for (int i = 0; i < len; i++) {
		arr.data[i] = num;
	}

	return arr;
}

/** 创建(转换)整数数组。
 *
 * @param len 数组长度。
 * @param data 整数数组->数组。
 * @return: 整数数组结构体。
 * */
IntArray createIntArray(int len, int data[]) {
	IntArray arr = {len, data};
	return arr;
}

/** 合并两个整数数组。
 *
 * @param arr1 整数数组结构体。
 * @param arr2 整数数组结构体。
 * @return 合并后的整数数组结构体。
 * */
IntArray concatIntArr(IntArray arr1, IntArray arr2) {
	IntArray arr = {arr1.len + arr2.len, (int*)malloc((arr1.len + arr2.len) * sizeof(int))};

	for (int i = 0; i < arr1.len; i++) {
		arr.data[i] = arr1.data[i];
	}

	for (int i = 0; i < arr2.len; i++) {
		arr.data[i + arr1.len] = arr2.data[i];
	}

	return arr;
}

/** 排除指定元素的整数数组。
 *
 * @param arr 整数数组结构体。
 * @param elem 指定元素。
 * @return 排除指定元素后的整数数组。
 */
IntArray excludeElem(IntArray arr, int elem) {
	IntArray res = {0, NULL};

	for (int i = 0; i < arr.len; i++) {
		if (arr.data[i]!= elem) {
			int *tmp = (int*)realloc(res.data, res.len * sizeof(int));

			if (checkMemoryInt(tmp)) free(res.data);
			else
			{
				res.data = tmp;
				res.data[res.len] = arr.data[i];
			}


			res.len++;
		}
	}

	return res;
}

/** 打印整数数组。
 *
 * @param arr 整数数组结构体。
 * @return null.
 */
void printIntArr(IntArray arr) {
	printf("[");

	for (int i = 0; i < arr.len; i++) {
		printf(i == arr.len - 1 ? "%d" : "%d, ", arr.data[i]);
	}

	printf("]\n");
}

/** 整数数组结构体的函数指针表
 *
 * @data createIntArray: 创建整数数组。
 * @data createIntCA: 创建相同值的整数数组。
 */
typedef struct {
	IntArray (*createArr)(int len, int *data);  // 创建整数数组
	IntArray (*createByComArgs)(int len, int num);  // 创建相同值的整数数组
	IntArray (*concat)(IntArray arr1, IntArray arr2);  // 合并两个整数数组
	IntArray (*exclude)(IntArray arr, int elem);  // 排除指定元素的整数数组
	void (*print)(IntArray arr);  // 打印整数数组
} S_IntArray;

const S_IntArray s_IntArray = {
	createIntArray, createIntCA,
	concatIntArr,
	excludeElem,
	printIntArr
};  // 整数数组结构体的函数指针表

/** 字符串数组结构体。
 *
 * @data len 数组长度。
 * @data data 数组元素指针->数组。
 * */
typedef struct {
	int len;  // 数组长度
	char **data;  // 数组元素指针->数组
} StrArray;

/** 创建字符串数组。
 *
 * @param len 数组长度。
 * @param data 字符串数组->数组。
 * @return 字符串数组结构体。
 */
StrArray createStrArray(int len, char **data) {
	StrArray arr = {len, data};
	return arr;
}

/** 创建相同值的字符串数组。
 *
 * @param len 数组长度。
 * @param string 字符串。
 * @return 字符串数组结构体。
 */
StrArray createStrCA(int len, char *string) {
	StrArray arr = {len, (char**)malloc(len * sizeof(char*))};

	for (int i = 0; i < len; i++) {
		arr.data[i] = strdup(string);
	}

	return arr;
}

/** 合并两个字符串数组。
 *
 * @param arr1 字符串数组1。
 * @param arr2 字符串数组2。
 * @return 合并后的字符串数组。
 */
StrArray concatStr(StrArray arr1, StrArray arr2) {
	StrArray arr = {arr1.len + arr2.len, (char**)malloc((arr1.len + arr2.len) * sizeof(char*))};

	for (int i = 0; i < arr1.len; i++) {
		arr.data[i] = strdup(arr1.data[i]);
	}

	for (int i = 0; i < arr2.len; i++) {
		arr.data[i + arr1.len] = strdup(arr2.data[i]);
	}

	return arr;
}

/** 排除指定字符串的字符串数组。
 *
 * @param arr 字符串数组。
 * @param string 指定字符串。
 * @return 排除指定字符串后的字符串数组。
 */
StrArray excludeStr(StrArray arr, char *string) {
	StrArray res = {0, NULL};

	for (int i = 0; i < arr.len; i++) {
		if (strcmp(arr.data[i], string) != 0) {
			const char **tmp = (char**)realloc(res.data, res.len * sizeof(char*));

			if (checkMemoryStr(tmp)) free(res.data);

			else
			{
				res.data = tmp;
				res.data[res.len] = strdup(arr.data[i]);

			}
			res.len++;

		}
	}

	return res;

}

/** 打印字符串数组。
 *
 * @param arr 字符串数组。
 * @return null.
 * */
void printStrArr(StrArray arr) {
	printf("[");

	for (int i = 0; i < arr.len; i++)
	{
		printf(i == arr.len - 1 ? "%s" : "%s, ", arr.data[i]);
	}

	printf("]\n");
}

/** 字符串数组结构体的函数指针表
 *
 * @data createStrArray: 创建字符串数组。
 * @data createStrCA: 创建相同值的字符串数组。
 * @data concat: 合并两个字符串数组。
 */
typedef struct {
	StrArray (*createArr)(int len, char **data);  // 创建字符串数组
	StrArray (*createByComArgs)(int len, char *string);  // 创建相同值的字符串数组
	StrArray (*concat)(StrArray arr1, StrArray arr2);  // 合并两个字符串数组
	StrArray (*exclude)(StrArray arr, char *string);  // 排除指定字符串的字符串数组
	void (*print)(StrArray arr);  // 打印字符串数组
} S_StrArray;

const S_StrArray s_StrArray = {
	createStrArray, createStrCA,
	concatStr,
	excludeStr,
	printStrArr
};  // 字符串数组结构体的函数指针表

/** 包括各种类型的数组结构体的结构体指针表。
 *
 * @data intArray: 整数数组结构体的函数指针表。
 * @data strArray: 字符串数组结构体的函数指针表。
 */
typedef struct {
	S_IntArray intArray;  // 整数数组结构体的函数指针表
	S_StrArray strArray;  // 字符串数组结构体的函数指针表
} ArrayTable;

ArrayTable Array = {
	s_IntArray,
	s_StrArray
};  // 包括各种类型的数组结构体的结构体指针表
