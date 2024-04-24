// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// !/user/bin/C

// -------------------------<Lenovo>----------------------------
// 传建时间: 24-4-24 上午11:02
// 当前项目名: C
// 编码模式: utf-8
// 注释:
// ------------------------<Lenovo>----------------------------


//
// Created by Lenovo on 24-4-24.
//

#include <stdio.h>
#include <stdlib.h>


// 定义二叉树节点的结构
typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

// 插入节点的函数
TreeNode* insertNode(struct TreeNode* root, int value) {
	if (root == NULL) {
		// 如果根节点为空，创建一个新节点作为根节点
		TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
		newNode->data = value;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else {
		// 根据值的大小递归地插入左侧或右侧
		if (value <= root->data) {
			root->left = insertNode(root->left, value);
		} else {
			root->right = insertNode(root->right, value);
		}
		return root;
	}
}

// 遍历二叉树的函数（这里使用中序遍历）
void inOrderTraversal(TreeNode* root) {
	if (root != NULL) {
		inOrderTraversal(root->left);
		printf("%d ", root->data);
		inOrderTraversal(root->right);
	}
}

// 测试示例
int main() {
	// 创建根节点
	TreeNode* root = NULL;

	// 插入节点
	root = insertNode(root, 10);
	root = insertNode(root, 5);
	root = insertNode(root, 15);
	root = insertNode(root, 3);
	root = insertNode(root, 7);

	// 遍历二叉树
	printf("In-order traversal: ");
	inOrderTraversal(root);

	return 0;
}

