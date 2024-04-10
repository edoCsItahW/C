/* 变量类型 */
#include <stdio.h>
//#include <math.h>
//extern int a;  声明其它文件中的变量
#include <windows.h>

/*
变量类型->枚举类型
			 ->void类型
			 ->派生类型
			 ->基本数据类型->int 整数类型
									-> char 字符类型
									-> float 浮点类型
									-> double 双精度浮点类型			
*/

// char 字符数据类型
// short 短整型
// int 整型
// long 长整型
// long long 更长的整型
// float 单精度浮点数
// double 双精度浮点数

/*
int main()
{	
	printf("各类型所占字节\n");

	printf("char的长度:%zu\n", sizeof(char));

	printf("short的长度:%zu\n", sizeof(short));

	printf("int的长度:%zu\n", sizeof(int));

	printf("long的长度:%zu\n", sizeof(long));

	printf("long long的长度:%zu\n", sizeof(long long));

	printf("float的长度:%zu\n", sizeof(float));

	printf("double的长度:%zu\n", sizeof(double));

	return 0;
}
*/

/*
int main()
{
	int num = 2;

	switch (num){
		case < 0:
			printf("小于0");
			break;
		case 0 <= num < 1:
			printf("0至1之间");
			break;
		default:
			printf("大于1");
	}

	return 0;
}
*/
/*
int BMI(int height);


int main() {
	int a;

	printf("输入你的体重:\n");

	scanf_s("%d", &a);

	printf("a的平方:%d\n", BMI(a));

	if (a < 0) {
		printf("体重小于0");
	}
	else if (0 <= a < 10) {
		printf("体重在0至10之间");
	}
	else {

		printf("体重大于10");

	}

	return 0;
}


int BMI(int height) {
	return pow(height, 2);
}
*/


//int main() {
//    int year;
//    printf("请输入一个年份:\n");
//    scanf_s("%d", &year);  // 赋值输入
//    
//    // 定义字典存储每个余数对应的生肖名称
//    const char* zodiacs[] = {
//        "猴", "鸡", "狗", "猪", "鼠", "牛", 
//		"虎", "兔", "龙", "蛇", "马", "羊",
//    };
//    
//    // 计算余数并根据余数索引字典获取生肖名称
//    int remainder = year % 12;
//    if (remainder >= 0 && remainder < 12) {
//        printf("%s", zodiacs[remainder]);
//    } else {
//        printf("非法输入%d", year);
//    }
//    
//    return 0;
//}

/*
int main() {
	
	int a = 1;

	while (a % 10 != 0) {
		
		printf("闪烁\n");
		Sleep(500);

		a++;

	}

	printf("等待\n");
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
