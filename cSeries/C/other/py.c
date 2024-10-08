// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// !/user/bin/C

// -------------------------<Lenovo>----------------------------
// 传建时间: 24-4-19 下午4:24
// 当前项目名: C
// 编码模式: utf-8
// 注释: 
// ------------------------<Lenovo>----------------------------


//
// Created by Lenovo on 24-4-19.
//

#include <stdio.h>
#include <Python.h>

static PyObject *method_fputs(PyObject *self, PyObject *args) {
	char *str = NULL, *filename = NULL;
	int bytes_copied = -1;

	if (!PyArg_ParseTuple(args, "ss", &str, &filename)) {
		PyErr_SetString(PyExc_TypeError, "Invalid arguments");
		return NULL;
	}

	// 确保 Python 已经初始化
	if (!Py_IsInitialized()) {
		Py_Initialize();
	}

	FILE *fp = fopen(filename, "w");

	if (fp == NULL) {
		perror("Error opening file");
		PyErr_SetString(PyExc_IOError, "Error opening file");
		return NULL;
	}

	if (str) {
		bytes_copied = fputs(str, fp);
	} else {
		PyErr_SetString(PyExc_ValueError, "str is NULL");
		fclose(fp);
		return NULL;
	}

	fclose(fp);

	return PyLong_FromLong(bytes_copied);
}

int main() {
	Py_Initialize(); // 确保 Python 初始化

	PyObject *args = PyTuple_Pack(2, PyUnicode_FromString("Hello, world!"), PyUnicode_FromString("test.txt"));
	if (args == NULL) {
		PyErr_Print();
		return 1;
	}

	PyObject *result = method_fputs(NULL, args);
	Py_DECREF(args); // 释放 args 的引用计数

	if (result == NULL) {
		PyErr_Print();
		return 1;
	}

	Py_DECREF(result); // 释放 result 的引用计数

	Py_Finalize(); // 清理 Python

	printf("program end.\n");
	return 0;
}
