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
 * @Date: 2024/05/16 上午9:55
 * @Commend: 定义基础类型结构体及其方法结构体
 ******************************************************/
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define INT_SIZE sizeof(int)
#define STR_SIZE sizeof(char*)

/* +---------+  +---------------+  +---------+  +---------------+
 * | listInt |  | listIntMethod |  | listStr |  | listStrMethod |
 * +---------+  +---------------+  +---------+  +---------------+
 * +----------------------------+  +----------------------------+
 * |           ListInt          |  |            ListStr         |
 * +----------------------------+  +----------------------------+
 * */

// *********** 定义函数 ***********

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

int checkMemory(void *arr) {
	if (arr == NULL) {
		perror("Memory allocation failed!");
		return -1;
	}
	return 0;
}

// *********** 定义基础类型结构体 ***********

/** 整数数组结构体。
 *
 * @data len: 数组长度。
 * @data data: 数组元素指针->数组。
 * */
typedef struct {
	int len;  // 数组长度
	int *data;  // 数组元素指针->数组
} listInt;  // 整数数组结构体

/** 字符串数组结构体。
 *
 * @data len 数组长度。
 * @data data 数组元素指针->数组。
 * */
typedef struct {
	int len;  // 数组长度
	char **data;  // 数组元素指针->数组
} listStr;  /* 字符串数组结构体 */

// *********** 定义基础类型结构体所具有方法结构体 ***********

typedef struct {
	listInt (*concat)(listInt arr1, listInt arr2);  // 合并两个整数数组
	listInt (*exclude)(listInt arr, int elem);  // 排除指定元素的整数数组
	void (*print)(listInt arr);  // 打印整数数组
} listIntMethod;  // 整数数组方法结构体

typedef struct {
	listStr (*concat)(listStr arr1, listStr arr2);  // 合并两个字符串数组
	listStr (*exclude)(listStr arr, char *string);  // 排除指定字符串的字符串数组
	void (*print)(listStr arr);  // 打印字符串数组
} listStrMethod;  /* 字符串数组方法结构体 */

// *********** 定义基础类型结构体所具有方法结构体的实现 ***********

/* ---------- 整数数组方法结构体的实现 ---------- */

/** 创建相同值的整数数组。
 *
 * @param len 数组长度。
 * @param num 数组元素值。
 * @return 整数数组结构体。
 * */
listInt createIntCA(int len, int num) {
	listInt arr = {len, (int*)malloc(len * INT_SIZE)};

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
listInt createInt(int len, int data[]) {
	listInt arr = {len, data};
	return arr;
}

/** 合并两个整数数组。
 *
 * @param arr1 整数数组结构体。
 * @param arr2 整数数组结构体。
 * @return 合并后的整数数组结构体。
 * */
listInt concatInt(listInt arr1, listInt arr2) {
	listInt arr = {arr1.len + arr2.len, (int*)malloc((arr1.len + arr2.len) * INT_SIZE)};

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
listInt excludeInt(listInt arr, int elem) {
	listInt res = {0, NULL};

	for (int i = 0; i < arr.len; i++) {
		if (arr.data[i]!= elem) {
			int *tmp = (int*)realloc(res.data, res.len * INT_SIZE);

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
void printInt(listInt arr) {
	printf("[");

	for (int i = 0; i < arr.len; i++) {
		printf(i == arr.len - 1 ? "%d" : "%d, ", arr.data[i]);
	}

	printf("]\n");
}

/* ---------- 字符串数组方法结构体的实现 ---------- */

/** 创建字符串数组。
 *
 * @param len 数组长度。
 * @param data 字符串数组->数组。
 * @return 字符串数组结构体。
 */
listStr createStr(int len, char **data) {
	listStr arr = {len, data};
	return arr;
}

/** 创建相同值的字符串数组。
 *
 * @param len 数组长度。
 * @param string 字符串。
 * @return 字符串数组结构体。
 */
listStr createStrCA(int len, char *string) {
	listStr arr = {len, (char**)malloc(len * STR_SIZE)};

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
listStr concatStr(listStr arr1, listStr arr2) {
	listStr arr = {arr1.len + arr2.len, (char**)malloc((arr1.len + arr2.len) * STR_SIZE)};

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
listStr excludeStr(listStr arr, char *string) {
	listStr res = {0, NULL};

	for (int i = 0; i < arr.len; i++) {
		if (strcmp(arr.data[i], string) != 0) {
			const char **tmp = (char**)realloc(res.data, res.len * STR_SIZE);

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
void printStr(listStr arr) {
	printf("[");

	for (int i = 0; i < arr.len; i++)
	{
		printf(i == arr.len - 1 ? "%s" : "%s, ", arr.data[i]);
	}

	printf("]\n");
}

// *********** 定义基础类型结构体所具有方法结构体的实例 ***********

listIntMethod intArrMethod = {
	concatInt,
	excludeInt,
	printInt
};

listStrMethod strArrMethod = {
	concatStr,
	excludeStr,
	printStr
};

// *********** 定义包装了基础类型和其方法结构体的结构体 ***********

typedef struct {
	listInt arr;  // 整数数组
	listIntMethod method;  // 整数数组方法结构体
} ListInt;

typedef struct {
	listStr arr;  // 字符串数组
	listStrMethod method;  // 字符串数组方法结构体
} ListStr;

// *********** 定义创建基础类型的函数 ***********

/** 创建(转换)整数数组。
 *
 * @param len 数组长度。
 * @param data 整数数组->数组。
 * @return: 整数数组结构体。
 * */
ListInt createIntList(int len, int data[]) {
	ListInt list = {createInt(len, data), intArrMethod};
	return list;
}

/** 创建相同值的整数数组。
 *
 * @param len 数组长度。
 * @param num 数组元素值。
 * @return 整数数组结构体。
 * */
ListInt createIntListCA(int len, int num) {
	ListInt list = {createIntCA(len, num), intArrMethod};
	return list;
}

/** 创建字符串数组。
 *
 * @param len 数组长度。
 * @param data 字符串数组->数组。
 * @return 字符串数组结构体。
 * */
ListStr createStrList(int len, char **data) {
	ListStr list = {createStr(len, data), strArrMethod};
	return list;
}

/** 创建相同值的字符串数组。
 *
 * @param len 数组长度。
 * @param string 字符串。
 * @return 字符串数组结构体。
 * */
ListStr createStrListCA(int len, char *string) {
	ListStr list = {createStrCA(len, string), strArrMethod};
	return list;
}

// *********** 定义数组类 ***********

/** 数组类。
 *
 * @data createIntList: 创建整数数组。
 * @data createIntListCA: 创建相同值的整数数组。
 * @data createStrList: 创建字符串数组。
 * @data createStrListCA: 创建相同值的字符串数组。
 * */
typedef struct {
	ListInt (*createInt)(int len, int data[]);  // 创建整数数组
	ListInt (*createIntByCA)(int len, int num);  // 创建相同值的整数数组
	ListStr (*createStr)(int len, char **data);  // 创建字符串数组
	ListStr (*createStrByCA)(int len, char *string);  // 创建相同值的字符串数组
} list_;  /* 数组类 */

// *********** 定义数组类的实例 ***********

list_ List = {
	createIntList,
	createIntListCA,
	createStrList,
	createStrListCA
};  // 数组类实例
