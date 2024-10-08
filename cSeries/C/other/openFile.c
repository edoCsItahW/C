// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: openFile.c
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/18 下午6:01
 * @Commend:
 *******************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>


typedef char* string;


typedef struct {
	_Bool (*exist)(string path);
	_Bool (*isDir)(string path);
} Path;


_Bool exist(string path) {
	if (access(path, F_OK) == 0) return 1;
	else return 0;
}


_Bool isDir(string path) {
	if (!exist(path))
		perror("Error: file not exist!");

	else {
		struct stat st;

		if (stat(path, &st) == 0) {
			if (S_ISDIR(st.st_mode)) return 1;
			else return 0;
		}
		else perror("Error: stat failed!");
	}
	return 0;
}
