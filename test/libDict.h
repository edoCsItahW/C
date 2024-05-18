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
 * @Date: 2024/05/16 上午10:59
 * @Commend:
 ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "_libList.h"
#define HASH_TABLE_SIZE 101 // 哈希表大小

// *********** 定义哈希函数 ****************

/** 哈希函数
 *
 * @param key: 键
 * @return: 哈希值
 * */
unsigned int hash(const char *key) {
	unsigned int hashval = 0;

	for (int i = 0; i < strlen(key); i++) {
		hashval += (hashval << 5) + key[i];
	}

	return hashval % HASH_TABLE_SIZE;
}

// *********** 定义基础类型结构体 ***********

/** 整数键值对
 *
 * @data key: 键
 * @data value: 值
 * @data next: 指向下一个节点的指针
 * */
typedef struct intPair_ {
	char *key;  // 键
	int value;  // 值
	struct intPair_ *next;  // 指向下一个节点的指针
} IntPair;

/** 字符串键值对
 *
 * @data key: 键
 * @data value: 值
 * @data next: 指向下一个节点的指针
 * */
typedef struct strPair_ {
	char *key;  // 键
	char *value;  // 值
	struct strPair_ *next;  // 指向下一个节点的指针,这个指针不是用来索引的,而是在发生碰撞时用来解决冲突的
} StrPair;

// *********** 定义字典结构体 ***********

/** 整数字典
 *
 * @data table: 哈希表数组
 * */
typedef struct {
	int len;  // 哈希表长度
	IntPair *table[HASH_TABLE_SIZE];  // 整数哈希表数组,每个元素是一个链表,通过key进行索引,而key是由hash函数计算得到的
} dictInt;

/** 字符串字典
 *
 * @data table: 哈希表数组
 */
typedef struct {
	int len;  // 哈希表长度
	StrPair **table;  // 字符串哈希表数组
} dictStr;

// *********** 定义字典方法结构体 ***********

/** 整型字典方法
 *
 * @data insert: 插入整型键值对的方法
 * */
typedef struct {
	void (*insert)(dictInt *dict, const char *key, int value);  // 插入整型键值对
	int (*get)(dictInt *dict, const char *key);  // 获取整型键值对
} intDictMethod;

typedef struct {

} strDictMethod;

// ************ 字典接口实现 ************

/* ------------- 整数字典方法实现 ---------- */

/** 字典初始化
 *
 * @param dict
 * @param key
 * @param value
 */
void insertInt(dictInt *dict, const char *key, int value) {
	unsigned int index = hash(key);

	IntPair *newPair = (IntPair *) malloc(sizeof(IntPair));

	strcpy(newPair->key, key);

	newPair->value = value;

	newPair->next = dict->table[index];

	dict->len = dict->len + 1;

	dict->table[index] = newPair;
}

int get(dictInt *dict, const char* key) {
	unsigned int index = hash(key);
		IntPair *current = dict->table[index];
		while (current != NULL) {
			if (strcmp(current->key, key) == 0) {
				return current->value;
			}
			current = current->next;
		}
		return -1; // 键未找到

}

// ************ 字典接口实列 ******************

intDictMethod intDictMethod_ = {
	insertInt,
	get
};

// ************ 定义包装了基础类型和其方法结构体的结构体 ************

typedef struct {
	dictInt *dict;
	intDictMethod method;
} DictInt;

void put(DictInt *dict, const char *key, int value) {
	unsigned int index = hash(key);

	IntPair *newPair = (IntPair *) malloc(sizeof(IntPair));

	newPair->key = strdup(key);

	newPair->value = value;

	dict->dict->table[index] = newPair;

	newPair->next = NULL;

	dict->dict->len++;

}

DictInt createDictInt(listStr *keys, listInt *values) {
	if (keys->len != values->len) {
		perror("Keys and values must have the same length!");
	}

	DictInt *dict = (DictInt *)malloc(sizeof(DictInt));

	dict->dict = (dictInt *)malloc(sizeof(dictInt));

	for (int i = 0; i < keys->len; i++)
	{
		put(dict, keys->data[i], values->data[i]);
	}

	dict->method = intDictMethod_;

	return *dict;

}

typedef struct {
	DictInt (*createInt)(listStr *keys, listInt *values);  // 创建整型字典
} Dict;

Dict dict = {
	createDictInt
};
