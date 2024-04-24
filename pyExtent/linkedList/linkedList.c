// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// !/user/bin/C

// -------------------------<Lenovo>----------------------------
// 传建时间: 24-4-19 下午4:10
// 当前项目名: C
// 编码模式: utf-8
// 注释: 
// ------------------------<Lenovo>----------------------------


//
// Created by Lenovo on 24-4-19.
//

#include <stdio.h>
// #include <stdint.h>
#include <stdlib.h>


typedef struct Node
{
	int data;
	struct Node* next;
} Node;


/**
 * @brief 创建节点
 * @param data 节点值
 * @return 新的节点
 */
Node* createNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	if (!newNode)
	{
		perror("Memory error");

		return NULL;
	}

	newNode->data = data;
	newNode->next = NULL;
	return newNode;

}

/**
 * 在C语言中，Node** head_ref中的**表示head_ref是一个指向指针的指针。具体来说，它是指向Node*类型的指针，而Node*是指向Node结构体的指针。这种双重指针通常用于在函数内部修改指向结构体（如链表节点或链表头）的指针。
 *
 *在这个append函数的上下文中，Node** head_ref允许函数修改传入的头节点指针本身，而不仅仅是修改头节点指针所指向的内容。这是非常有用的，因为在链表的操作中，我们有时需要改变头节点（例如，当向空链表添加第一个节点时）。
 *
 *以下是为什么我们需要使用Node**而不是Node*的几个原因：
 *
 *处理空链表：当链表为空时，头节点指针head本身可能是NULL。如果我们只传递Node* head到函数中，我们无法在函数内部改变head本身的值（即，使其指向一个新的节点），因为函数接收的是头节点指针的一个拷贝。但是，如果我们传递Node** head_ref，我们就可以改变head_ref所指向的地址，即原始的头节点指针head。
 *
 *链表的通用操作：使用Node**使得我们的函数更加通用，无论链表是否为空，都可以正确地添加新节点。
 *
 *在append函数中，当链表为空时，我们将*head_ref（即原始的head指针）设置为新创建的节点。这样，调用append函数的外部代码中的head指针现在指向新添加的节点。
 *
 *简而言之，Node** head_ref允许我们在函数内部修改传入的头节点指针，而不仅仅是修改它指向的内容。这是C语言中处理指针和动态数据结构时常见的做法。
 */
void append(Node** head, int data)
{
	Node* new_node = createNode(data);

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		Node* current = *head;

		while (current->next != NULL)
		{
			current = current->next;
		}

		current->next = new_node;
	}

}

/**
 *
 * @param node
 */
void printList(Node* node)
{

	while (node != NULL)
	{
		printf("%d -> ", node->data);

		node = node->next;
	}

	printf("NULL\n");
}

int main() {

	Node* head = NULL;

	for (int i = 0; i <= 10; i++)
		append(&head, i);

	printList(head);
	return 0;

}

/**
 * @brief 指针相关
 *
 * 在声明 int *p = &num; 时，* 是一个类型说明符，用于声明 p 是一个指向整数的指针。  \n
 * 在表达式 *p 中，* 是一个解引用操作符，用于获取指针 p 所指向地址处的值。
 *
 * 在大多数现代系统上，地址通常是一个比 int 更大的数据类型（比如 size_t 或 uintptr_t），因此直接将地址转换为 int 可能会导致截断或溢出，这取决于地址的大小和 int 类型的大小。
 *
 * *&num 实际上是对 num 的一个取地址和解引用的组合，它应该等价于 num 本身。
 *
 * 当打印指针时，应该将指针转换为 void* 类型，并使用 %p 格式说明符。对于 uintptr_t 类型的值，您可以使用 %lx 或 %lu（取决于您的系统和编译器），但通常最好使用 %lx 或 %llx（对于 64 位值）来确保正确打印。
 *
 * 标准库提供了一些类型，如 size_t 和 uintptr_t。size_t 通常用于表示对象的大小或数组的索引，它是无符号的，并且足够大以存储任何对象的大小。uintptr_t 是一个无符号整数类型，它的大小足以存储一个指针的整数值。这些类型提供了一种在需要时将指针转换为整数类型的方法，以便进行某些特殊的操作或打印。
 *
 * @param
 *
 * @return
 */
void pointer()
{
	int num=2014;

	int *p=&num;

	uintptr_t d = (uintptr_t)&num;

	printf("num Address = 0x%p, num=%d, %lu\n", &num, num, sizeof &num);

	printf("p = 0x%p, *p=%d\n", p, *p);

	printf("d = 0x%lx\n", d);

	printf("%d\n", *&num);
}
