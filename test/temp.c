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
 * @Date: 2024/05/21 上午10:05
 * @Commend:
 *******************************************************/
#include <stdarg.h>
#include <stdio.h>

//va_arg()

// 字节对齐, 参数1: 字节对齐值, 默认为 1
#pragma pack(1)

//
#pragma data_seg
#pragma code_seg

//
#pragma optimize()  //

// 编译的情况下发送字面字符串常量到标准输出。
#pragma message("Hello, world!")
#define MESSAGE "message"
#pragma message("MESSAGE: " MESSAGE)

#pragma comment(lib, "user32.lib")  // 指定链接库文件名

// once参数在头文件（*.h）的开头使用，目的是防止该文件被包含(#include)多次。
#pragma once

// hdrstop（即HeaDeR STOP），表示仅编译这前的头文件，后方不再编译。
#pragma hdrstop

// 编译器警告，禁用特定警告。
#pragma warning(push)  // 保存当前警告状态
#pragma warning(disable: 4996, once: 4005, error: 4018)  // disable: 4996 34: 不显示4996和34警告；once: 4005: 4005号警告仅报告一次；error: 4018: 把4018号警告作为一个错误
#pragma warning(pop)  // 恢复警告状态

enum Color { RED, GREEN = 100, BLUE };  // 枚举类型,会自动递增

// 枚举的前向声明
typedef enum Animal Animal;

// 引用后赋值
enum Animal { CAT, DOG = 100, BIRD };

// C11静态断言
_Static_assert(sizeof(int) == 4, "int is not 4 bytes long");  // 断言失败会导致编译错误
/*_Static_assert的基本语法如下：
	_Static_assert(constant_expression, string_literal);
constant_expression：一个在编译时能够求值的常量表达式，其值必须能够被隐式转换为bool类型。
	string_literal：如果constant_expression为假，编译器将输出这个字符串字面量作为错误信息的一部分。
 */

//C11字节对齐说明符
_Alignas(16) int a; // 变量a的对齐值为16字节
_Alignas(double) char array[sizeof(double)];
// 这将确保array数组的对齐方式与double类型相同

//int printf("%zu\n", alignof(int));   // 计算int类型对齐值

/*
宽字符（Wide Character）
宽字符是一个能够表示更广泛字符集（如Unicode）的字符类型。在C语言中，宽字符通常使用wchar_t类型来表示。这个类型的大小（即它能够表示的字符范围）取决于编译器和平台，但它通常足够大，以容纳Unicode中的大多数字符。

宽字符串（Wide String）
宽字符串是由宽字符组成的字符串。在C语言中，宽字符串通常以L前缀开头，并使用宽字符字面量（如L'A'）或宽字符串字面量（如L"Hello, World!"）来表示。与常规字符串不同，宽字符串能够表示包含非ASCII字符的文本。

多字节字符（Multibyte Character）
多字节字符是指使用多个字节来表示的字符。这通常用于表示那些不能在一个字节中完全表示的字符集，如中文字符集。在C语言中，多字节字符和字符串的处理依赖于当前的区域设置（locale）和编码方式。例如，UTF-8是一种常用的多字节编码方式，它使用可变数量的字节来表示Unicode字符。
*/

volatile int i = 0;  // 定义一个volatile变量，它的值在程序执行期间可能会改变，编译器不会对其进行优化。

signed int j = 0;  // 定义一个带符号整数变量。

// 泛型选择关键字_Generic
#define PRINT_TYPE(X) _Generic((X), \
	char: puts("char"),                \
	short : puts("short"),             \
	int : puts("int"),                 \
	long : puts("long"),               \
	default: puts("unknown"))

// 复合字面量
int *arr_ptr = (int[]){1, 2, 3};

typedef struct {
	int x;
	int y;
} Point;

Point *p = &(Point){1, 2};  // 定义并初始化一个Point类型的变量。

// 内联函数
inline int square(int x) {
	return x * x;
}  // 当编译器看到main函数中对max的调用时，它可能会选择将max函数的代码直接嵌入到调用处，而不是执行正常的函数调用过程。这样做的好处是可以减少函数调用的开销，但也可能导致代码膨胀。

// 宏函数
#define SQUARE(x) ((x) * (x))  // 定义一个宏函数，它返回x的平方。

// 字符串化操作符
#define STRINGIFY(x) #x  // 字符串化操作符，它将宏参数x转换为一个字符串。
// printf("%s\n", STRINGIFY(hello, world!));  // 输出"hello"

// 连接操作符
#define CONCAT(x, y) x ## y  // 连接操作符，它将两个宏参数连接成一个单独的符号。
// int var123 = 10;
// printf("%d\n", CONCAT(var, 123));  // 输出10

// 取消定义
#undef PI  // 取消定义PI宏

// 宏类型定义
#define INT_PTR int*  // 宏类型定义，它定义了一个指向整数的指针类型。

// asm函数
asm("addl %1, %0;"
	: "=r"(sum)  // 输出
	: "r"(x), "0"(y)  // 输入
	:
	"cc"  // 约束
	);

int x, y = 10;
int sum;

printf("x + y = %d\n", sum);  // 输出10

#define MY_ARG(type, value) do { \
    if (_Generic((type), int: 1, float: 2, double: 3) == 1) { \
         // 对 int 类型的操作
printf("Value is an int: %d\n", (int)(value));
} else if (_Generic((type), int: 1, float: 2, double: 3) == 2) {
	// 对 float 类型的操作
	printf("Value is a float: %f\n", (float)(value));
} else if (_Generic((type), int: 1, float: 2, double: 3) == 3) {
	// 对 double 类型的操作
	printf("Value is a double: %f\n", (double)(value));
} else {
	printf("Unsupported type\n");
} \
} while (0)

	int main() {
		int i = 10;
		float f = 3.14f;
		double d = 2.71828;

		MY_ARG(int, i);    // 输出: Value is an int: 10
		MY_ARG(float, f);  // 输出: Value is a float: 3.140000
		MY_ARG(double, d); // 输出: Value is a double: 2.718280

		return 0;
	}
