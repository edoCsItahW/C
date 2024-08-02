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
 * @Date: 2024/05/20 下午4:05
 * @Commend:
 *******************************************************/
#include "libArray.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define MALLOC(size, type) (type*)malloc(size * sizeof(type))  // 申请内存
#define CHECKMEM(ptr) if (ptr == NULL) exit(EXIT_FAILURE)  // 检查内存是否申请成功

typedef void (*arrPrintFuncType)(void*, int, int);  // 打印函数类型

/** 定义打印函数结构体
 *
 * @data pFunc 打印函数指针
 * */
typedef struct {
	arrPrintFuncType pFunc;  // 打印函数指针
} arrPrintFunc;

/** 打印整数数组
 *
 * @param data 整数指针
 * @param idx 数组下标
 * @param len 数组长度
 * */
void arrPrintInt(void *data, int idx, int len) {  // 打印整数数组
	printf(idx == len - 1 ? "%d" : "%d, ", *(int *)data);
}

/** 打印字符串数组
 *
 * @param data 字符串指针
 * @param idx 数组下标
 * @param len 数组长度
 */
void arrPrintString(void *data, int idx, int len) {  // 打印字符串数组
	printf(idx == len - 1 ? "'%s'" : "'%s', ", (char *)data);
}

/** 打印数组元素
 *
 * @param type 数组元素类型
 * @return 打印函数指针
 * */
arrPrintFunc* arrPrintType(const Type type) {
	arrPrintFunc * pFunc = (arrPrintFunc *)malloc(sizeof(arrPrintFunc));

	if (type == Int) {
		pFunc->pFunc = arrPrintInt;
	}
	else if (type == String) {
		pFunc->pFunc = arrPrintString;
	}
	else {
		printf("Error: unsupported type.\n");
		free(pFunc);
		exit(EXIT_FAILURE);
	}

	return pFunc;
}

/** 创建数组
 *
 * @param data 数组元素指针数组
 * @param len 数组长度
 * @param type 数组元素类型
 * @return 数组结构体
 * */
Array *createArr_(int len, Type type, ...) {
	va_list args;

	va_start(args, type);

	Array *arr = MALLOC(1, Array);

	CHECKMEM(arr);

	arr->len = len;

	arr->type = type;

	arr->data = MALLOC(len, void*);

	for (int i = 0; i < len; i++) {
		if (type == Int)
		{
			int *tmp = (int *)malloc(sizeof(int));  // va_arg(args, int);

			*tmp = va_arg(args, int);

			arr->data[i] = (void *)tmp;

		}
		else if (type == String)
		{
			char **tmp = (char **)malloc(sizeof(char *)); // va_arg(args, char **);

			*tmp = va_arg(args, char *);

			arr->data[i] = *(void **)tmp;
		}
		else {
			perror("Error: unsupported type ");
			free(arr);
			exit(EXIT_FAILURE);
		}
	}

	va_end(args);

	return arr;
}

#define createArr(len, first, ...) createArr_(len, getType(first), first, ##__VA_ARGS__)  // 创建数组

/** 将整数数组转换为数组结构体
 *
 * @param data 整数数组
 * @param len 数组长度
 * @return 数组结构体
 * */
Array* convertInt(int data[], int len) {
	void **arr = (void **)malloc(len * sizeof(void *));

	CHECKMEM(arr);

	for (int i = 0; i < len; i++) {
		arr[i] = (void *)(data + i);
	}

	Array* arrInt = MALLOC(1, Array);

	arrInt->len = len;
	arrInt->type = Int;
	arrInt->data = arr;

	return arrInt;

}

/** 将字符串数组转换为数组结构体
 *
 * @param data 字符串数组
 * @param len 数组长度
 * @return 数组结构体
 * */
Array* convertString(char *data[], int len) {
	void **arr = (void **)malloc(len * sizeof(void *));

	CHECKMEM(arr);

	for (int i = 0; i < len; i++)
	{
		arr[i] = (void *)(data + i);
	}

	Array* arrString = MALLOC(1, Array);

	arrString->len = len;
	arrString->type = String;
	arrString->data = arr;

	return arrString;
}

/** 创建全为知道值的数组
 *
 * @param data 数组元素指针
 * @param type 数组元素类型
 * @param len 数组长度
 * @return 数组结构体
 * */
Array* createByRepeat_(int len, Type type, void* data) {

	Array* arr = MALLOC(1, Array);

	CHECKMEM(arr);

	arr->len = len;
	arr->type = type;

	arr->data = MALLOC(len, void*);

	CHECKMEM(arr->data);

	for (int i = 0; i < len; i++){
		arr->data[i] = (void *)data;
	}

	return arr;

}

#define createByRepeat(len, value) createByRepeat_(len, getType(value), value)  // 创建全为知道值的数组

/** 销毁数组
 *
 * @param arr 数组结构体
 * */
void destroyArr(Array *arr) {
	if (arr == NULL) return;

	free(arr);

}

/** 从数组中移除元素
 *
 * @param arr 数组结构体
 * @param idx 数组下标
 */
void arrRemove(Array* arr, int idx) {
	if (idx < 0 || idx >= arr->len) {
		perror("Error: index out of range.\n");
		exit(EXIT_FAILURE);
	}

	if (0 < idx < arr->len - 1) {
		for (size_t i = idx; i < arr->len - 1; i++) {
			arr->data[i] = arr->data[i + 1];
		}
	}
	arr->len--;

	arr->data = realloc(arr->data, arr->len * sizeof(void*));

	CHECKMEM(arr->data);

}

/** 向数组中追加元素
 *
 * @param arr 数组结构体
 * @param data 数组元素指针
 */
void append(Array* arr, void* data) {
	arr->data = realloc(arr->data, (arr->len + 1) * sizeof(void*));

	CHECKMEM(arr->data);

	arr->data[arr->len] = data;
	arr->len++;

}

/** 打印数组
 *
 * @param arr 数组结构体
 * */
void printArr(Array* arr) {

	printf("[");

	arrPrintFunc * pFunc = arrPrintType(arr->type);

	for (int i = 0; i < arr->len; i++) {
		pFunc->pFunc(arr->data[i], i, arr->len);
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
Array* concat(Array* arr1, Array* arr2) {

	Array* arr = MALLOC(1, Array);

	CHECKMEM(arr);

	arr->len = arr1->len + arr2->len;
	arr->type = arr1->type;
	arr->data = MALLOC(arr->len, void*);

	CHECKMEM(arr->data);

	for (int i = 0; i < arr->len; i++) {
		if (i < arr1->len) {
			arr->data[i] = arr1->data[i];
		}
		else {
			arr->data[i] = arr2->data[i - arr1->len];
		}
	}

	return arr;

}

/** 数组切片
 *
 * @param start 开始下标
 * @param end 结束下标
 * @return 数组结构体
 * */
Array* range(int start, int end) {
	int len = end - start + 1;

	Array* arr = MALLOC(1, Array);

	CHECKMEM(arr);

	arr->len = len;
	arr->type = Int;
	arr->data = MALLOC(len, void*);

	CHECKMEM(arr->data);

	for (int i = 0; i < len; i++) {
		int *tmp = (int *)malloc(sizeof(int));

		*tmp = start + i;

		arr->data[i] = (void*)tmp;
	}

	return arr;

}

/** 数组元素去重
 *
 * @param arr 数组结构体
 * @param data 数组元素指针
 */
void exclude(Array arr, void *data) {

	int pos = 0;

	for (int i = 0; i < arr.len; i++) {
		if (arr.data[i] == data) {
			pos++;
		}
		else {
			arr.data[i - pos] = arr.data[i];
		}

	}
}

S_arrMethod Arr = {
	.converInt = convertInt,
	.convertString = convertString,
	.destroy = destroyArr,
	.remove = arrRemove,
	.append = append,
	.print = printArr,
	.concat = concat,
	.range = range,
	.exclude = exclude
};
