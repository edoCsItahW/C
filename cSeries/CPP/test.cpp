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
#include <functional>
#include <stdexcept>


template<typename T, typename... Args>
class Decorator {
private:
	std::function<T(Args...)> _func;
	bool _flag;

public:
	Decorator(bool flag = false): _flag(flag) {}

	T wrapper(Args... args) {
		try {
			return _func(args...);
		}
		catch (std::exception& e) {
			throw e;
		}
	}

	std::function<T(Args...)> operator()(std::function<T(Args...)> func) {
		_func = func;
		return std::bind(&Decorator::wrapper, this, std::placeholders::_1, std::placeholders::_2);
		// or use
		// return [this](Args... args) { return this->wrapper(args...); };
	}
};


int test(int x, int y) {
	return x + y;
}


int main() {
	auto f = Decorator<int, int, int>(true)(test);
	std::cout << f(1, 2) << std::endl;
	return 0;
}
