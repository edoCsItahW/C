// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// -------------------------<edocsitahw>----------------------------
// 传建时间: 2024/05/08 下午8:44
// 当前项目名: test
// 编码模式: utf-8
// 注释:
// -------------------------<edocsitahw>----------------------------
#include <stdio.h>
#include "arrlib.h"
//#include "dictlib.h"


int main() {

	char *k[] = {"hello", "world", "c", "language", "is", "awesome"};

	Array keys = convertString(k, 5);

	int value[] = {1, 2, 3, 4, 5};

	Array values = convertInt(value, 5);

//	Dict dict = createDict(&keys, &values);

	Arr.print(keys);

	return 0;
}

