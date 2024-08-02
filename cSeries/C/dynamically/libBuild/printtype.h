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
 * @Date: 2024/05/18 下午11:45
 * @Commend:
 *******************************************************/
#include "typelib.h"
#include <stdio.h>
#include <stdlib.h>

typedef void (*ArrPrintMethod)(void* data, int idx, int len);

typedef void (*DictPrintMethod)(char* keys, void* values, int idx, int len);

typedef struct {
	ArrPrintMethod printType;
} arrPrintMethod;

typedef struct {
	DictPrintMethod printType;
} dictPrintMethod;

typedef struct {
	void* printType;
} PrintMethod;

typedef arrPrintMethod* (*apMethod)(Type type);

typedef dictPrintMethod* (*dpMethod)(Type type);

void arrPrintInt(void *data, int idx, int len) {printf(idx == len - 1 ? "%d" : "%d, ", *(int *)data);}

void arrPrintString(void *data, int idx, int len) {printf(idx == len - 1 ? "%s" : "%s, ", *(char **)data);}

void dictPrintInt(char* key, void *value, int idx, int len) {
	printf(idx == len ? "'%s': %d" : "'%s': %d, ", key, *(int *)value);
}

void dictPrintString(char* key, void *value, int idx, int len) {printf(idx == len ? "'%s': %s" : "'%s': %s, ", key, *(char **)value);}

arrPrintMethod* arrPrintType(Type type) {
	arrPrintMethod* printMethod = (arrPrintMethod*)malloc(sizeof(arrPrintMethod));

	if (type.value == Int.value) {
		printMethod->printType = arrPrintInt;
	}
	else if (type.value == String.value) {
		printMethod->printType = arrPrintString;
	}
	else {
		fprintf(stderr, "Unsupported type: %s\n", type.name);
		exit(EXIT_FAILURE);
	}
	return printMethod;
}

dictPrintMethod* dictPrintType(Type type) {

	dictPrintMethod* printMethod = (dictPrintMethod*)malloc(sizeof(dictPrintMethod));

	if (type.value == Int.value) {
		printMethod->printType = dictPrintInt;
	}
	else if (type.value == String.value) {
		printMethod->printType = dictPrintString;
	}
	else {
		fprintf(stderr, "Unsupported type: %s\n", type.name);
		exit(EXIT_FAILURE);
	}
	return printMethod;
}

PrintMethod* chooseType(Type structType) {
	PrintMethod* printMethod = (PrintMethod*)malloc(sizeof(PrintMethod));

	if (structType.value == Array_.value) {
		printMethod->printType = (void*)arrPrintType;
	}
	else if (structType.value == Dict_.value) {
		printMethod->printType = (void*)dictPrintType;
	}
	else {
		fprintf(stderr, "Unsupported type: %s\n", structType.name);
		exit(EXIT_FAILURE);
	}

	return printMethod;
}
