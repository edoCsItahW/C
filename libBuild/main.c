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
 * @Date: 2024/05/20 ����9:52
 * @Commend:
 *******************************************************/
#include <omp.h>





int main() {

	int var1, var2, var3;

	char *thread1 = "Thread 1";
	char *thread2 = "Thread 2";
	char *thread3 = "Thread 3";

	#pragma omp parallel private(var1, var2) shared(var3) {

	}

	return 0;
}
