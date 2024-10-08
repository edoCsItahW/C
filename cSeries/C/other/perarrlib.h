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
 * @Date: 2024/05/17 上午11:41
 * @Commend: 为数组结构体做准备,同时直接暴露内部实现的文件
 ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typelib.h"


/** 打印方法(回调函数)类型定义
 * */
typedef void (*p_printMethod)(void *data, int idx, int len);

/** 打印方法结构体定义
 *
 * @data pMethod 打印方法(回调函数)
 */
typedef struct {
	p_printMethod pMethod;
} printMethod;

/** 打印int类型数组
 *
 * @param data 数组
 * @param idx 数组下标
 * @param len 数组长度
 * */
void printInt(void *data, int idx, int len) {printf(idx == len - 1 ? "%d" : "%d, ", *(int *)data);}

/** 打印string类型数组
 *
 * @param data 数组
 * @param idx 数组下标
 * @param len 数组长度
 * */
void printString(void *data, int idx, int len) {printf(idx == len - 1 ? "%s" : "%s, ", *(char **)data);}

/** 根据类型获取打印方法(简单工厂模式)
 *
 * @param type
 * @return
 */
printMethod* printType(const Type type) {
	printMethod* p_method = (printMethod*)malloc(sizeof(printMethod));

	if (type.value == Int.value) {
		p_method->pMethod = printInt;
		return p_method;
	}
	else if (type.value == String.value) {
		p_method->pMethod = printString;
		return p_method;
	}
	else {
		fprintf(stderr, "Error: Invalid %s.\n", type.name);
		exit(EXIT_FAILURE);
	}
}
