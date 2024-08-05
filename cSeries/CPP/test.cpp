// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

//
// Created by Lenovo on 24-5-6.
//
#include <functional>

class Sample
{
	public:
	Sample() {}
	int test() {}
	int test(int i) {}
};

Sample sample1;
auto pFun1 = std::bind((int(Sample::*)())&Sample::test
								  ,&sample1);

std::function pFun2 = std::bind((int(Sample::*)(int))&Sample::test
								  ,&sample1
								  ,std::placeholders::_1);