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