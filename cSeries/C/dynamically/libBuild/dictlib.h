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
 * @Date: 2024/05/18 下午1:03
 * @Commend:
 ******************************************************/
#include "arrlib.h"
#include <string.h>
#define MAX_SIZE 101

typedef void (*dictPrintFuncType)(char *key, void *value, int idx, int len);

/** 定义打印函数结构体
 *
 * @data pFunc 打印函数指针
 * */
typedef struct {
	dictPrintFuncType pFunc;  // 打印函数指针
} dictPrintFunc;

void dictPrintInt(char* key, void *value, int idx, int len) {
	printf(idx == len ? "'%s': %d" : "'%s': %d, ", key, *(int *)value);
}

void dictPrintString(char* key, void *value, int idx, int len) {
	printf(idx == len ? "'%s': %s" : "'%s': %s, ", key, *(char **)value);
}

static dictPrintFunc * dictPrintType(const Type type) {
	dictPrintFunc* pFunc = (dictPrintFunc *)malloc(sizeof(dictPrintFunc));

	if (type.value == Int.value) {
		pFunc->pFunc = dictPrintInt;
	}
	else if (type.value == String.value) {
		pFunc->pFunc = dictPrintString;
	}
	else {
		printf("Error: unsupported type.\n");
		exit(EXIT_FAILURE);
	}

	return pFunc;
}

// ******************** 定义哈希函数 ************************

/** 哈希函数
 *
 * @brief 哈希函数,将字符串key转换为一个整数hash值,范围在0-MAX_SIZE
 *
 * @param key 待哈希的字符串
 * @return hash值
 * */
unsigned int hash(const char *key) {
	unsigned int hash = 0;

	for (int i = 0; i < strlen(key); i++) {
		hash += (hash << 5) + key[i];  // 5位移位,加上字符ASCII码
	}

	return hash % MAX_SIZE;   // 取模,使得哈希值在0-MAX_SIZE范围内
}

// ******************** 定义字典结构 ************************

/** 键值对结构
 *
 * @data key: 键
 * @data value: 值
 * @data next: 指向下一个键值对的指针
 * */
typedef struct pair {
 char *key;   // 键
 void *value; // 值
 struct pair *next;  // 指向下一个键值对的指针
} Pair;

// ******************** 定义字典结构 ***********************

/** 字典结构
 *
 * @data size: 字典大小
 * @data table: 哈希表,数组,大小为size,每个元素是一个链表
 * */
typedef struct {
	int size;
	Type type;
	Pair *table[MAX_SIZE];
} Dict;

// ******************** 字典操作函数实现 **********************

/** 向字典中添加键值对
 *
 * @param dict 字典
 * @param key 键
 * @param value 值
 * */
void put(Dict *dict, const char *key, void *value) {

	unsigned int index = hash(key);

	Pair *pair = (Pair*)malloc(sizeof(Pair));

	pair->key = strdup(key);

	pair->value = value;

	dict->table[index] = pair;

	pair->next = NULL;

}

/** 从字典中删除键值对
 *
 * @param dict 字典
 * @param key 键
 * */
void* get(Dict *dict, const char* key) {
	unsigned int index = hash(key);

	Pair *current = dict->table[index];

	while (current != NULL) {
		if (strcmp(current->key, key) == 0) {
			return (void*)current->value;
		}

		current = current->next;
	}

}

/** 打印字典
 *
 * @param dict
 */
void printDict(Dict dict) {
	printf("{");

	dictPrintFunc* method = dictPrintType(dict.type);

	int count = 0;

	for (int i = 0; i < MAX_SIZE; i++) {

		Pair* current = dict.table[i];

		if (current != NULL) count++;

		while (current != NULL) {

			method->pFunc(dict.table[i]->key, dict.table[i]->value, count, dict.size);

			current = current->next;
		}

	}

	printf("}\n");

	free(method);

}

/** 创建字典
 *
 * @param keys 键数组
 * @param values 值数组
 * @param type 字典类型
 * @return 字典
 * */
Dict createDict(Array keys, Array values, Type type) {
	if (keys.len != values.len) perror("Error: keys and values have different lengths");

	Dict *dict = (Dict*)malloc(sizeof(Dict));

	for (int i = 0; i < MAX_SIZE; i++) {
		dict->table[i] = NULL;
	}

	dict->type = type;

	dict->size = keys.len;

	for (int i = 0; i < keys.len; i++) {
		put(dict, *(char**)keys.data[i], values.data[i]);
	}

	return *dict;

}
