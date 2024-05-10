// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// -------------------------<edocsitahw>----------------------------
// 传建时间: 2024/05/08 下午8:40
// 当前项目名: test
// 编码模式: utf-8
// 注释:
// -------------------------<edocsitahw>----------------------------
#include <stdio.h>

/* C语言中无法直接将数组作为函数参数传递，而int data[]也不能作为结构体的成员。
 *
 * */
typedef struct arr {
	int len;
	int *data;
} Array;

typedef void (*CallbackFunc)(int);

Array createArray(int arr[], int len) {
	Array a = {len, arr};
	return a;
}

Array map(CallbackFunc f, Array a) {
	for (int i = 0; i < a.len; i++) {
		f(a.data[i]);
	}
	return a;
}
