// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: stdapi.h
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/09 下午9:24
 * @Commend: This is the header file of the standard API and this api is used to define the cpp function api for python extension.
 *******************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include "pybind11/pybind11.h"


using namespace std;
namespace py = pybind11;


class String {
public:
	String(): input("") {}
	explicit String(bool flag): input(flag ? "True" : "False") {}

	template <typename T>
	explicit String(const T& value) {
		ostringstream oss;
		oss << value;
		input = oss.str();
	}

	explicit operator string() const {
		return input;
	}

	friend ostream& operator<<(ostream& os, const String& str) {
		os << str.input;
		return os;
	}

	[[nodiscard]] string getInput() const { return input; }

private:
	string input;
};
