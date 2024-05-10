// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// -------------------------<edocsitahw>----------------------------
// ����ʱ��: 2024/05/08 ����7:51
// ��ǰ��Ŀ��: test
// ����ģʽ: utf-8
// ע��:
// -------------------------<edocsitahw>----------------------------
#include <stdio.h>

/* �ڶ�ָ����мӼ�����ʱ,����1��ʾ1���洢����Ԫ����
 *
 * �ڶ�ָ����мӼ�����ʱ������1��ʾ1���洢��Ԫ�ĳ��ȣ�����ζ��ָ���1ʱ��ָ����һ���洢��Ԫ��λ�ã���1ʱ��ָ����һ���洢��Ԫ��λ�á�
 * */

/* "*p + 1"��"*(p + 1)"�����ò�ͬ
 *
 * *����������ȼ�����+-
 * */

void iSort() {
	void insertionSort(int arr[], int n);

	int arr[] = {5, 2, 8, 3, 9, 1};

	int n = sizeof arr / sizeof arr[0];

	printf("δ��������\n");

	for (int i = 1; i < n; i++) {
		printf("%d", arr[i]);
	}

	insertionSort(arr, n);

	printf("\n���������\n");

	for (int i = 0; i < n; i++) {
		printf("%d", arr[i]);
	}

}

void insertionSort(int arr[], int n) {
	// int arr[] ��ʾ��������������Ϊ�����ĺ���

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

	if (a) {  // aΪ0,Ϊfalse,��Ȼ��������
		printf("if (a) �ǿ������е�\n");
	}

	if (a = b) {  // a = b, ���� a == b, ����b��ֵ��������a, ���صĽ����������ֵΪ4,Ϊtrue,���Կ�������
		printf("if (a = b) �ǿ������е�, ��ʱ��a: %d\n", a);
	}

	if (a >= b) {  // ��ʱ a = b = 4, ���Ե���,Ϊtrue,��������
		printf("if (a >= b) �ǿ������е�, ��ʱ��a: %d\n", a);
	}

	if (!(b - a)) {  // ��ʱ b - a = 0, ���Բ�����0,Ϊtrue,��������
		printf("if (!(b - a)) �ǿ������е�, ��ʱ��a: %d\n", a);
	}
}

// ���нض�ת��,����С�����ֶ���,��������������
void typeTrans() {
	printf("%d\n", (int)(11.0 / 3 + 0.5));
}

// ��C��C++��,����ʹ�ó�ʼ���б�����ʼ��һ������ʱ,����ṩ��Ԫ�ز����������������,ʣ���λ�ûᱻ�Զ����Ϊ0.������Ϊ����Ϊ"���ֳ�ʼ��"
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
