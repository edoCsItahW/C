// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

#include <stdio.h>
#include <stdlib.h>


int main()
{
	int var = 20;   /* ʵ�ʱ��������� */
	int *ip;        /* ָ����������� */

	ip = &var;  /* ��ָ������д洢 var �ĵ�ַ */

	printf("var �����ĵ�ַ: %p\n", &var);

	/* ��ָ������д洢�ĵ�ַ */
	printf("ip �����洢�ĵ�ַ: %p\n", ip);

	/* ʹ��ָ�����ֵ */
	printf("*ip ������ֵ: %d\n", *ip);

	return 0;
}