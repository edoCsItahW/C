// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: C
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/05/22 下午6:55
 * @Commend:
 *******************************************************/
#include "dict.h"

Dict* countLetter(char* str) {
	Dict* dict = emptyDict(Int);

	for (int i = 0; i < strlen(str); i++) {

		char key[2] = {str[i], '\0'};

		if (include(dict, key))
		{
			Pair* pair = getPair(dict, key);

			int* currentV = (int*)malloc(sizeof(int));

			CHECKMEM(currentV);

			*currentV = *(int*)pair->value + 1;

			free(pair->value);

			pair->value = (void*)currentV;
		}
		else {
			int* value = (int*)malloc(sizeof(int));

			CHECKMEM(value);

			*value = 1;

			updata(dict, key, (void*)value);
		}
	}

	return dict;

}
