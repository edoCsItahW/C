// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/* �������� */
#include <stdio.h>
//#include <math.h>
//extern int a;  ���������ļ��еı���
#include <windows.h>

/*
��������->ö������
			 ->void����
			 ->��������
			 ->������������->int ��������
									-> char �ַ�����
									-> float ��������
									-> double ˫���ȸ�������			
*/

// char �ַ���������
// short ������
// int ����
// long ������
// long long ����������
// float �����ȸ�����
// double ˫���ȸ�����

/*
int main()
{	
	printf("��������ռ�ֽ�\n");

	printf("char�ĳ���:%zu\n", sizeof(char));

	printf("short�ĳ���:%zu\n", sizeof(short));

	printf("int�ĳ���:%zu\n", sizeof(int));

	printf("long�ĳ���:%zu\n", sizeof(long));

	printf("long long�ĳ���:%zu\n", sizeof(long long));

	printf("float�ĳ���:%zu\n", sizeof(float));

	printf("double�ĳ���:%zu\n", sizeof(double));

	return 0;
}
*/

/*
int main()
{
	int num = 2;

	switch (num){
		case < 0:
			printf("С��0");
			break;
		case 0 <= num < 1:
			printf("0��1֮��");
			break;
		default:
			printf("����1");
	}

	return 0;
}
*/
/*
int BMI(int height);


int main() {
	int a;

	printf("�����������:\n");

	scanf_s("%d", &a);

	printf("a��ƽ��:%d\n", BMI(a));

	if (a < 0) {
		printf("����С��0");
	}
	else if (0 <= a < 10) {
		printf("������0��10֮��");
	}
	else {

		printf("���ش���10");

	}

	return 0;
}


int BMI(int height) {
	return pow(height, 2);
}
*/


//int main() {
//    int year;
//    printf("������һ�����:\n");
//    scanf_s("%d", &year);  // ��ֵ����
//    
//    // �����ֵ�洢ÿ��������Ӧ����Ф����
//    const char* zodiacs[] = {
//        "��", "��", "��", "��", "��", "ţ", 
//		"��", "��", "��", "��", "��", "��",
//    };
//    
//    // �����������������������ֵ��ȡ��Ф����
//    int remainder = year % 12;
//    if (remainder >= 0 && remainder < 12) {
//        printf("%s", zodiacs[remainder]);
//    } else {
//        printf("�Ƿ�����%d", year);
//    }
//    
//    return 0;
//}

/*
int main() {
	
	int a = 1;

	while (a % 10 != 0) {
		
		printf("��˸\n");
		Sleep(500);

		a++;

	}

	printf("�ȴ�\n");
	Sleep(1000);
	
	return 1;
}
*/

int main() {

	enum Days {
		Sunday,
		Monday,
		Tuesday,
		Wednesday,
		Thursday,
		Friday,
		Saturday
	} today;

	today = Thursday;

	if (today == Sunday) {
		printf("Today is Sunday.\n");
	}

	today = Thursday;
	switch (today) {
	case Monday:
		printf("Today is Monday.\n");
		break;
	case Thursday:
		printf("Today is Thursday.\n");
		break;
	default:
		printf("Today is some other day.\n");
	}

	return 0;
}
