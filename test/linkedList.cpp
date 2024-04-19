// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// !/user/bin/C

// -------------------------<Lenovo>----------------------------
// 传建时间: 24-4-18 下午12:57
// 当前项目名: C
// 编码模式: utf-8
// 注释: 
// ------------------------<Lenovo>----------------------------

#include <iostream>
#include "F:/ProgramFiles/Anaconda3/Lib/site-packages/pybind11/include/pybind11/pybind11.h"

namespace py = pybind11;

struct Node
{
	int data;
	Node* next;
};

Node* createNode(int data)
{

	Node* newNode = new Node;

	if (!newNode)
	{
		std::cerr << "Memory error" << std::endl;
		return nullptr;
	}

	newNode->data = data;
	newNode->next = nullptr;

	return newNode;
}

// void append(Node** head, int data)
// {
// 	std::cout << "running append" << std::endl;
//
// 	Node* new_node = createNode(data);
//
// 	if (*head == nullptr)
// 	{
// 		*head = new_node;
// 	}
// 	else
// 	{
// 		Node* current = *head;
//
// 		while (current->next != nullptr)
// 		{
// 			current = current->next;
// 		}
//
// 		current->next = new_node;
// 	}
//
// 	std::cout << "end append" << std::endl;
//
// }

void append(Node*& head, int data)
{
	Node* new_node = createNode(data);

	if (new_node)
	{
		if (head == nullptr)
		{
			head = new_node;
		}
		else
		{
			Node* current = head;

			while (current->next != nullptr)
			{
				current = current->next;
			}

			current->next = new_node;
		}
	}

}

void printList(Node* node)
{
	while (node != nullptr)
	{
		std::cout << node->data << " -> ";
		node = node->next;
	}

	std::cout << "NULL" << std::endl;

}


// int main()
// {
// 	Node* head = nullptr;
//
// 	append(&head, 1);
// 	append(&head, 2);
// 	append(&head, 3);
//
// 	printList(head);
//
// 	return 0;
//
// }


PYBIND11_MODULE(linkedList, m)
{
	m.doc() = "链表模块";

	py::class_<Node>(m, "Node")
		.def(py::init<>())
		.def_readwrite("data", &Node::data)
		.def_readwrite("next", &Node::next);

	m.def("createNode", &createNode, "创建节点");

	m.def("append", [](py::object node_ptr, int value)
	{
		Node* ptr = py::cast<Node*>(node_ptr);
		append(ptr, value);
		return ptr;
	}, "添加节点");

	m.def("printList", &printList, "打印链表");
}
