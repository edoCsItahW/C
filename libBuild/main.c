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
 * @Date: 2024/05/20 ÉÏÎç9:52
 * @Commend:
 *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "array.h"


int findPrime(int firstNum) {

	while (1) {

		for (int n = 1; n <= 4; n = (2 * n + 1)) if (firstNum % n == n - 2) return firstNum;

		firstNum++;

	}

	return 0;

}


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


int main() {

//	printf("The first prime number is: %d\n", findPrime(1));

	Array* arr = createArr(10, 5, 3, 5, 2, 7, 1, 9, 4, 6, 8);

	Arr.print(quickSort(arr));

	return 0;
}
