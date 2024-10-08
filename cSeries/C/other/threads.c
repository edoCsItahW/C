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
 * @Date: 2024/05/23 上午10:06
 * @Commend:
 *******************************************************/
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

void *thread_function(void *arg) {
	int thread_id = *((int *)arg);
	printf("Hello from thread %d\n", thread_id);
	pthread_exit(NULL);
}

int main() {
	pthread_t threads[NUM_THREADS];
	int thread_args[NUM_THREADS];
	int result_code, i;

	// 创建多个线程
	for (i = 0; i < NUM_THREADS; i++) {
		thread_args[i] = i;
		printf("Creating thread %d\n", i);
		result_code = pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
		if (result_code != 0) {
			perror("Thread creation failed");
			return -1;
		}
	}

	// 等待所有线程结束
	for (i = 0; i < NUM_THREADS; i++) {
		result_code = pthread_join(threads[i], NULL);
		if (result_code != 0) {
			perror("Thread join failed");
			return -1;
		}
	}

	return 0;
}
