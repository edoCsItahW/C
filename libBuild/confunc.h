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
 * @Date: 2024/05/22 下午6:55
 * @Commend:
 *******************************************************/
#include "dict.h"

/** 计数字母出现次数
 *
 * @param str 字符串
 * @return Dict* 字典
 * */
Dict* countLetter(char* str) {
	Dict* dict = emptyDict(Int);

	for (int i = 0; i < strlen(str); i++) {

		char key[2] = {str[i], '\0'};

		if (include(dict, key))
		{
			Pair* pair = getPair(dict, key);

			int* currentV = (int*)malloc(sizeof(int));

			CHECKMEM(currentV);

			*currentV = *(int*)pair->value + 1;

			free(pair->value);

			pair->value = (void*)currentV;
		}
		else {
			int* value = (int*)malloc(sizeof(int));

			CHECKMEM(value);

			*value = 1;

			updata(dict, key, (void*)value);
		}
	}

	return dict;

}


/** 快速排序
 *
 * @param arr 数组
 * @return Array* 排序后的数组
 * */
Array* quickSort(Array* arr) {

	if (arr->len <= 1) return arr;

	int pivot = *(int*)(arr->data[0]);

	Array* left = emptyArr(Int), *middle = emptyArr(Int), *right = emptyArr(Int);

	for (int i = 0; i < arr->len; i++)
	{

		int current = *(int *)(arr->data[i]);

		if (current < pivot) {

			Arr.append(left, arr->data[i]);
		}
		else if (current == pivot) {

			Arr.append(middle, arr->data[i]);

		}
		else {

			Arr.append(right, arr->data[i]);

		}
	}

	return Arr.concat(Arr.concat(quickSort(left), middle), quickSort(right));

}


int findPrime(int firstNum) {

	while (1) {

		for (int n = 1; n <= 4; n = (2 * n + 1)) if (firstNum % n == n - 2) return firstNum;

		firstNum++;

	}

	return 0;

}
