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
 * @Date: 2024/05/27 上午10:06
 * @Commend:
 *******************************************************/
#include <stdio.h>
#include <unistd.h>


void input(FILE* stream, char* instruction) {
	fprintf(stream, "%s\n", instruction);

	fflush(stream);

}


int main() {  // int argc, char *argv[]
	// 打开一个管道并执行cmd程序
	FILE *pipe = popen("cmd", "w");
	if (!pipe) {
		fprintf(stderr, "Error opening pipe.\n");
		return 1;
	}

	input(pipe, "cd ../lauchor");

	input(pipe, ".\\hmcl-dev-3.5.7.247.exe");

	input(pipe, "cd ../spigot");

	input(pipe, "java -jar ./spigot-1.20.4.jar");

	char inp[100];

	while (1) {

		fgets(inp, sizeof(inp), stdin);

		inp[strcspn(inp, "\n")] = 0;

		input(pipe, inp);
	}

	// 关闭管道
	pclose(pipe);

	return 0;
}
