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
 * @Date: 2024/05/20 上午9:52
 * @Commend:
 *******************************************************/
#include "dict.h"

int main() {
	Array* arr = createArr(5, 1, 2, 3, 4, 5);

	Dict* dict = createDict(createArr(5, "a", "b", "c", "d", "e"), arr);

	printDict(dict);

	printf("%d", *(int*)get(dict, "a"));

	return 0;
}
