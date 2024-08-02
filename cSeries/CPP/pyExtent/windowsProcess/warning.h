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
 * @Date: 2024/07/03 下午3:51
 * @Commend:
 *******************************************************/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


int WARNING_LEVEL = 0;


typedef enum {
	DEBUG,
	INFO,
	WARNING,
	ERROR_,
	CRITICAL
} WarnLevel;


void asprintf(char** strp, const char* format, ...) {
	va_list args;
	va_start(args, format);

	size_t len = _vscprintf(format, args) + 1;
	*strp = (char*)calloc(len, sizeof(char));

	vsprintf(*strp, format, args);

	va_end(args);
}


void warn(const WarnLevel level, const char* format, ...) {
	if (level > WARNING_LEVEL) {
		va_list args;
		va_start(args, format);

		vprintf(format, args);

		va_end(args);
	}
}


#define warnColor(level, format, ...) \
do {                                  \
char* colorText;                      \
asprintf(&colorText, "\033[31m%s\033[0m", format); \
warn(level, colorText, __VA_ARGS__); \
free(colorText);                      \
} while (0)


#define alert(format, ...) \
do {                       \
char* buffer;              \
asprintf(&buffer, format, __VA_ARGS__); \
MessageBox(NULL, buffer, "Alert", MB_OK | MB_ICONWARNING); \
free(buffer);              \
} while (0)
