// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

//
// Created by Lenovo on 24-5-6.
//
#include <iostream>
#include <iomanip>

//int main() {
//	std::cout << "Hello, world!" << std::endl;
//
//	int v1 = 0, v2 = 0;
//
//	std::cin >> v1 >> v2;
//
//	std::cout << "The sum of " << v1 << " and " << v2 << " is " << v1 + v2 << std::endl;
//
//	int sum = 0, value = 0;
//
//	while (std::cin >> value)
//		sum += value;
//
//	std::cout << "The sum of the values is " << sum << std::endl;
//
//	return 0;
//}
int main() {
	double func(int n);

	std::cout << std::fixed << std::setprecision(2) << func(10) << std::endl;

	return 0;
}

double func(int n) {
	int i = 0, sum = 0;
	double total = 0.0;

	while (i < n) {
		i++;

		sum += i;

		double result = 1.0 / sum;

		total += result;
	}

	return total;
}
