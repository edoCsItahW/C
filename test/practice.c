// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// -------------------------<edocsitahw>----------------------------
// 传建时间: 2024/05/08 下午7:51
// 当前项目名: test
// 编码模式: utf-8
// 注释:
// -------------------------<edocsitahw>----------------------------
#include <stdio.h>

/* 在对指针进行加减运算时,数字1表示1个存储单的元长度
 *
 * 在对指针进行加减运算时，数字1表示1个存储单元的长度，这意味着指针加1时会指向下一个存储单元的位置，减1时会指向上一个存储单元的位置。
 * */

/* "*p + 1"和"*(p + 1)"的作用不同
 *
 * *运算符的优先级高于+-
 * */

void iSort() {
	void insertionSort(int arr[], int n);

	int arr[] = {5, 2, 8, 3, 9, 1};

	int n = sizeof arr / sizeof arr[0];

	printf("未排序数组\n");

	for (int i = 1; i < n; i++) {
		printf("%d", arr[i]);
	}

	insertionSort(arr, n);

	printf("\n排序后数组\n");

	for (int i = 0; i < n; i++) {
		printf("%d", arr[i]);
	}

}

void insertionSort(int arr[], int n) {
	// int arr[] 表示接受整数数组作为参数的函数

	int i, key, j;

	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;


		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	}
}

// if (a = b) ? if (a == b)
void whichCanRun() {
	int a = 0, b = 4;

	if (a) {  // a为0,为false,当然不能运行
		printf("if (a) 是可以运行的\n");
	}

	if (a = b) {  // a = b, 不是 a == b, 所以b的值被赋给了a, 返回的结果即被赋的值为4,为true,所以可以运行
		printf("if (a = b) 是可以运行的, 此时的a: %d\n", a);
	}

	if (a >= b) {  // 此时 a = b = 4, 所以等于,为true,可以运行
		printf("if (a >= b) 是可以运行的, 此时的a: %d\n", a);
	}

	if (!(b - a)) {  // 此时 b - a = 0, 所以不等于0,为true,可以运行
		printf("if (!(b - a)) 是可以运行的, 此时的a: %d\n", a);
	}
}

// 进行截断转换,即将小数部分丢弃,仅保留整数部分
void typeTrans() {
	printf("%d\n", (int)(11.0 / 3 + 0.5));
}

// 在C或C++中,当你使用初始化列表来初始化一个数组时,如果提供的元素不足以填充整个数组,剩余的位置会被自动填充为0.这种行为被称为"部分初始化"
void fewArgs() {
	int arr[10] = {1, 2, 3, 4, 5};

	for (int i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}

	// output: 1 2 3 4 5 0 0 0 0 0

}

int main() {
	iSort();
}
