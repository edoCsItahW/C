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
 * @Date: 2024/05/22 下午2:56
 * @Commend:
 *******************************************************/
#include "array.h"
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

	if (type == Int) {
		pFunc->pFunc = dictPrintInt;
	}
	else if (type == String) {
		pFunc->pFunc = dictPrintString;
	}
	else {
		printf("Error: unsupported type.\n");
		free(pFunc);
		exit(EXIT_FAILURE);
	}

	return pFunc;
}

unsigned int hash(const char *key) {
	unsigned int hash = 0;

	for (int i = 0; i < strlen(key); i++) {
		hash += (hash << 5) + key[i];  // 5位移位,加上字符ASCII码
	}

	return hash % MAX_SIZE;   // 取模,使得哈希值在0-MAX_SIZE范围内
}

typedef struct pair {
	char *key;   // 键
	void *value; // 值
	struct pair *next;  // 指向下一个键值对的指针
} Pair;

typedef struct {
	int size;
	Type type;
	Pair *table[MAX_SIZE];
} Dict;

void put(Dict *dict, const char *key, void *value) {

	unsigned int index = hash(key);

	Pair *pair = (Pair*)malloc(sizeof(Pair));

	pair->key = strdup(key);

	pair->value = value;

	dict->table[index] = pair;

	pair->next = NULL;

}

void* get(Dict *dict, const char* key) {
	unsigned int index = hash(key);

	Pair *current = dict->table[index];

	while (current != NULL) {
		if (strcmp(current->key, key) == 0) {
			return (void*)current->value;
		}

		current = current->next;
	}

	printf("Error: key '%s' not found.\n", key);
	exit(EXIT_FAILURE);

}

void printDict(Dict* dict) {
	printf("{");

	dictPrintFunc* method = dictPrintType(dict->type);

	int count = 0;

	for (int i = 0; i < MAX_SIZE; i++) {

		Pair* current = dict->table[i];

		if (current != NULL) count++;

		while (current != NULL) {

			method->pFunc(dict->table[i]->key, dict->table[i]->value, count, dict->size);

			current = current->next;
		}

	}

	printf("}\n");

	free(method);

}

Dict* createDict(Array* keys, Array* values) {
	if (keys->len != values->len) perror("Error: keys and values have different lengths");

	Type type = values->type;

	Dict *dict = (Dict*)malloc(sizeof(Dict));

	for (int i = 0; i < MAX_SIZE; i++) {
		dict->table[i] = NULL;
	}

	dict->type = type;

	dict->size = keys->len;

	for (int i = 0; i < keys->len; i++) {
		put(dict, (char*)keys->data[i], values->data[i]);
	}

	return dict;

}
