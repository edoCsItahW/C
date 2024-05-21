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
#include "arrlib_.h"

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

			free(tmp);
		}
		else if (type.value == String.value)

			arr.data[i] = (void *)(va_arg(args, char **));
		else {
			printf("Error: unsupported type.\n");

			exit(EXIT_FAILURE);

		}

	}

	va_end(args);

	return arr;

}

SarrMethod Arr = {
	.create = createArr,   // 创建数组
	.createByRepeat = createByRepeat,  // 创建全为重复值的数组
	.convertInt = convertInt,  // 将整数数组转换为数组结构体
	.convertString = convertString,  // 将字符串数组转换为数组结构体
	.print = printArr,  // 打印数组
	.concat = concat,  // 拼接数组
	.exclude = exclude  // 排除数组中的指定元素
};
