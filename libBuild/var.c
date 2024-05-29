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
 * @Date: 2024/05/28 上午11:34
 * @Commend:
 *******************************************************/
#include "type.h"


typedef struct {
	void *data;
	int size;
	Type type;
} Var;

#define newVar(data, type) (Var){data, sizeof(data), type}

Var v = newVar(10, Int);
