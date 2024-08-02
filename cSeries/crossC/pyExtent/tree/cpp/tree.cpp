// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// !/user/bin/C

// -------------------------<Lenovo>----------------------------
// 传建时间: 24-4-24 下午1:45
// 当前项目名: C
// 编码模式: utf-8
// 注释:
// ------------------------<Lenovo>----------------------------


//
// Created by Lenovo on 24-4-24.
//
#include <iostream>
#include <memory> // For std::unique_ptr

// 定义二叉树节点的结构
struct TreeNode {
	int data;
	std::unique_ptr<TreeNode> left;
	std::unique_ptr<TreeNode> right;

	TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// 插入节点的函数
std::unique_ptr<TreeNode> insertNode(std::unique_ptr<TreeNode>& root, int value) {
	if (!root) {
		// 如果根节点为空，创建一个新节点作为根节点
		root = std::make_unique<TreeNode>(value);
	} else {
		// 根据值的大小递归地插入左侧或右侧
		if (value <= root->data) {
			root->left = insertNode(root->left, value);
		} else {
			root->right = insertNode(root->right, value);
		}
	}
	// 使用std::move来移动unique_ptr的所有权
	return std::move(root);
}

// 遍历二叉树的函数（这里使用中序遍历）
void inOrderTraversal(const TreeNode* root) {
	if (root != nullptr) {
		inOrderTraversal(root->left.get());
		std::cout << root->data << " ";
		inOrderTraversal(root->right.get());
	}
}

// 测试示例
int main() {
	// 创建根节点
	std::unique_ptr<TreeNode> root = nullptr;

	// 插入节点，注意这里root在insertNode内部已经被更新
	insertNode(root, 10);
	insertNode(root, 5);
	insertNode(root, 15);
	insertNode(root, 3);
	insertNode(root, 7);

	// 遍历二叉树
	std::cout << "In-order traversal: ";
	inOrderTraversal(root.get());
	std::cout << std::endl; // 添加换行符以改善输出格式

	return 0;
}