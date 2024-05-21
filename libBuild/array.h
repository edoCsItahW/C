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
 * @Date: 2024/05/21 下午6:34
 * @Commend:
 *******************************************************/
#include "type.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define MALLOC(size, type) (type*)malloc(size * sizeof(type))
#define CHECKMEM(ptr) if (ptr == NULL) exit(EXIT_FAILURE)

typedef void (*arrPrintFuncType)(void*, int, int);

typedef struct {
	arrPrintFuncType pFunc;
} arrPrintFunc;

void arrPrintInt(void *data, int idx, int len) {  // 打印整数数组
	printf(idx == len - 1 ? "%d" : "%d, ", *(int *)data);
}

void arrPrintString(void *data, int idx, int len) {  // 打印字符串数组
	printf(idx == len - 1 ? "'%s'" : "'%s', ", (char *)data);
}

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

typedef struct {
	int len;
	void **data;
	Type type;
} Array;

Array *_createArr(int len, Type type, ...) {
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

#define createArr(len, first, args...) _createArr(len, getType(first), first, ##args)

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

Array* _createByRepeat(int len, Type type, void* data) {

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

#define createByRepeat(len, value) _createByRepeat(len, getType(value), value)

void destroyArr(Array *arr) {
	if (arr == NULL) return;

	free(arr);

}

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

void append(Array* arr, void* data) {
	arr->data = realloc(arr->data, (arr->len + 1) * sizeof(void*));

	CHECKMEM(arr->data);

	arr->data[arr->len] = data;
	arr->len++;

}

void printArr(Array* arr) {

	printf("[");

	arrPrintFunc * pFunc = arrPrintType(arr->type);

	for (int i = 0; i < arr->len; i++) {
		pFunc->pFunc(arr->data[i], i, arr->len);
	}

	printf("]\n");

	free(pFunc);
}

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
