// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: DataFrameImpl
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/25 上午10:07
 * @Commend:
 *******************************************************/

#include "tree.h"

Tree::BinaryTree::BinaryTree()
    : _root(nullptr) {}

Tree::BinaryTree::BinaryTree(const std::map<std::string, std::any>& map)
    : _root(std::make_shared<Node>()) {
    _root = createNode("root", map);
}

auto Tree::BinaryTree::root() const -> std::shared_ptr<Node> { return _root; }

auto Tree::BinaryTree::createNode(const std::string& name, const std::any& value) -> std::shared_ptr<Node> {
    auto node  = std::make_shared<Node>();
    node->name = name;

    if (value.type() == typeid(std::map<std::string, std::any>)) {
        std::cout << "nname: " << name << std::endl;
        int count = 0;
        for (auto& [k, v] : std::any_cast<std::map<std::string, std::any>>(value)) {
            if (count == 0)
                node->left = createNode(k, v);
            else if (count == 1)
                node->right = createNode(k, v);
            else
                throw std::range_error(std::format("{}: BinaryTree only support 2 children nodes, but {} received {}!", __FUNCTION__, name, count));
            count++;
        }
    }
    else {
        std::cout << "vname: " << name << std::endl;
        node->value = value;
    }

    return node;
}

int Tree::BinaryTree::_deep(const std::shared_ptr<Node>& node) const {
    if (node == nullptr) return 0;
    return 1 + std::max(_deep(node->left), _deep(node->right));
}

int Tree::BinaryTree::deep() const { return _deep(_root); }

Tree::BinaryTree& Tree::BinaryTree::copy() const {
    auto tree = std::make_shared<BinaryTree>();
    if (_root == nullptr) return *tree;
    auto node   = std::make_shared<Node>();
    node->name  = _root->name;
    node->value = _root->value;
    if (_root->left != nullptr) node->left = createNode(_root->left->name, _root->left->value);
    if (_root->right != nullptr) node->right = createNode(_root->right->name, _root->right->value);
    tree->_root = node;
    return *tree;
}