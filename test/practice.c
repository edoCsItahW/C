// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// -------------------------<edocsitahw>----------------------------
// 传建时间: 2024/05/08 下午7:51
// 当前项目名: test
// 编码模式: utf-8
// 注释:
// -------------------------<edocsitahw>----------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// 指针加减
/* 在对指针进行加减运算时,数字1表示1个存储单的元长度
 *
 * 在对指针进行加减运算时，数字1表示1个存储单元的长度，这意味着指针加1时会指向下一个存储单元的位置，减1时会指向上一个存储单元的位置。
 * */

// 指针运算符优先级
/* "*p + 1"和"*(p + 1)"的作用不同
 *
 * *运算符的优先级高于+-
 * */

// 二进制补码
/* 有符号二进制数10001101的补码为
 *
 * 1. 第一位为1表示负数,为0表示正数
 * 2. 负数则取反在加1,正数补码使其本身
 * 3. 10001101的补码为11110010
 * 4. 加1为11110011
 * */

// 串数据结构特殊性
/*数据结构串是由零个或多个字符组成的有限序列。它的特殊性主要体现在以下几个方面：

不可变性：在很多编程语言中，字符串属于不可变的数据类型，即一旦创建就无法改变其中的字符。这种不可变性可以带来一定的安全性和稳定性。
// 不可变性示例（Java）
String str = "Hello";
str = str + " World"; // 实际上是创建了一个新的字符串，而不是在原字符串上添加内容
序列性：字符串是由字符组成的有序序列，每个字符在字符串中都有固定的位置索引，可以通过索引来访问特定位置的字符。
// 序列性示例（Python）
s = "Hello"
	print(s[0])  # 输出'H'
	print(s[1])  # 输出'e'

 * */

// 对称矩阵表示的图是无向图
/*对称矩阵表示的图是无向图。在无向图中，每条边都是双向的，因此邻接矩阵会呈现出对称的特性。具体来说，如果图中有顶点i到顶点j的边，则邻接矩阵中的第i行第j列和第j行第i列的元素值将相等。

以下是一个无向图的邻接矩阵示例：

1 2 3 4
1 0 1 1 0
2 1 0 1 1
3 1 1 0 0
4 0 1 0 0*/

// 无向图边表示法
/*(1, 2) 通常用于表示无向图的边，因为它没有明确表示边的方向。
<1, 2> 是有向图的边的常见表示方法。这里，1 是起点（或称为尾），2 是终点（或称为头），尖括号表示边的方向性*/

/*对于广义表((a, b), (c, d))，表尾是((c, d))。*/

// 二叉树最小高度
/*要计算包含125个节点的二叉树的最小高度，可以利用二叉树的性质和一些简单的计算公式来解决这个问题。

首先，我们知道一个完全二叉树的节点数和高度之间存在关系。

对于包含n个节点的完全二叉树：

		如果树的高度为h，则它至少有2^h个节点，至多有2^(h+1)-1个节点。
		如果一个完全二叉树的节点数落在2^h和2^(h+1)-1之间，那么它的高度为h。
		针对125个节点的二叉树，我们可以使用上述关系反推最小高度：

		节点数：125
		如果高度为h，则节点数至少为：2^h
	因此，2^h <= 125

		解出h的最小整数值，即为最小高度。
		为了求解上述不等式，我们可以进行一些计算：

		2^h <= 125

		取对数得到：
		h <= log2(125)
			   h <= 6.96
			因此，最小的高度h为7。
 * */

// 逗号表达式的值是其最右侧子表达式的结果
void child()
{
	int x, y, z;
	x = (y = 4, z = 8, z = 16);

	printf("x: %d, y: %d, z: %d\n", x, y, z);
}

void complex() { printf("%d\n", 6 > 4 && 2 || 8 < 4); }

void iSort()
{
	void insertionSort(int arr[], int n);

	int arr[] = {5, 2, 8, 3, 9, 1};

	int n = sizeof arr / sizeof arr[0];

	printf("未排序数组\n");

	for (int i = 1; i < n; i++)
	{
		printf("%d", arr[i]);
	}

	insertionSort(arr, n);

	printf("\n排序后数组\n");

	for (int i = 0; i < n; i++)
	{
		printf("%d", arr[i]);
	}
}

void insertionSort(int arr[], int n)
{
	// int arr[] 表示接受整数数组作为参数的函数

	int i, key, j;

	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;


		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	}
}

// if (a = b) ? if (a == b)
void whichCanRun()
{
	int a = 0, b = 4;

	if (a)
	{ // a为0,为false,当然不能运行
		printf("if (a) 是可以运行的\n");
	}

	if (a = b)
	{ // a = b, 不是 a == b, 所以b的值被赋给了a, 返回的结果即被赋的值为4,为true,所以可以运行
		printf("if (a = b) 是可以运行的, 此时的a: %d\n", a);
	}

	if (a >= b)
	{ // 此时 a = b = 4, 所以等于,为true,可以运行
		printf("if (a >= b) 是可以运行的, 此时的a: %d\n", a);
	}

	if (!(b - a))
	{ // 此时 b - a = 0, 所以不等于0,为true,可以运行
		printf("if (!(b - a)) 是可以运行的, 此时的a: %d\n", a);
	}
}

// 进行截断转换,即将小数部分丢弃,仅保留整数部分
void typeTrans() { printf("%d\n", (int)(11.0 / 3 + 0.5)); }

// 在C或C++中,当你使用初始化列表来初始化一个数组时,如果提供的元素不足以填充整个数组,剩余的位置会被自动填充为0.这种行为被称为"部分初始化"
void fewArgs()
{
	int arr[10] = {1, 2, 3, 4, 5};

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}

	// output: 1 2 3 4 5 0 0 0 0 0
}

int main()
{

}
