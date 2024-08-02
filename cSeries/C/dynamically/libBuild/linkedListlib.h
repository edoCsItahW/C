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
 * @Date: 2024/05/20 下午5:03
 * @Commend:
 *******************************************************/
#include "arrlib.h"

typedef void (*LListPrintFuncType)(void*);

typedef struct {
	LListPrintFuncType pFunc;
} lListPrintFunc;

void printIntLList(void* data) {
	printf("<value: %d> -> ", *(int*) data);
}

void printStringLList(void* data) {
	printf("<value: %s> -> ", *(char**) data);
}

lListPrintFunc* lListPrintType(const Type type) {
	lListPrintFunc* pFunc = (lListPrintFunc*)malloc(sizeof(lListPrintFunc));

	if (type.value == Int.value) pFunc->pFunc = printIntLList;
	else if (type.value == String.value) pFunc->pFunc = printStringLList;
	else {
		printf("Error: Invalid type for linked list\n");
		exit(EXIT_FAILURE);
	}

	return pFunc;
}

typedef struct node {
	void *data;
	Type type;
	struct node *next;
} Node;

void addNode(Node *head, void *data) {
	Node node = {data, head->type, NULL};

	if (head->next == NULL) {
		head->next = &node;
	}

}

Node* createNode(Type type, void *data) {
	Node *node = (Node*) malloc(sizeof(Node));

	if (node) {
		node->data = data;
		node->next = NULL;
	}

	return node;
}

Node* convertIntLList(Array arr) {
	Node dummy;

	dummy.next = NULL;

	Node* tail = &dummy;

	for (int i = 0; i < arr.len; i++) {
		Node* newNode = createNode(arr.type, arr.data[i]);

		tail->next = newNode;

		tail = newNode;

	}

	dummy.next->type = arr.type;

	return dummy.next;
}

void printLList(Node* head) {
	Node* current = head;

	lListPrintFunc* pFunc;

	if (current == NULL) {
		perror("Error: Linked list is empty\n");
		exit(EXIT_FAILURE);
	}
	else {
		pFunc = lListPrintType(head->type);
	}

	while (current != NULL) {
		pFunc->pFunc(current->data);
		current = current->next;
	}

	printf("NULL\n");

	free(pFunc);
}
