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
 * @Date: 2024/09/06 上午10:07
 * @Commend:
 *******************************************************/

#ifndef DATAFRAMEIMPL_TREE_H
#define DATAFRAMEIMPL_TREE_H
#pragma once

#include <any>
#include <format>
#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <vector>

namespace Tree {
    class Tree {
        public:
            [[nodiscard]] virtual int deep() const   = 0;
            [[nodiscard]] virtual Tree& copy() const = 0;
    };

    class BinaryTree : public Tree {
        private:
            typedef struct node {
                    std::string name;
                    std::shared_ptr<node> left;
                    std::shared_ptr<node> right;
                    std::any value;
            } Node;

            std::shared_ptr<Node> _root;
            [[nodiscard]] int _deep(const std::shared_ptr<Node>& node) const;

        public:
            BinaryTree();
            explicit BinaryTree(const std::map<std::string, std::any>& map);
            [[nodiscard]] std::shared_ptr<Node> root() const;
            [[nodiscard]] int deep() const override;
            [[nodiscard]] BinaryTree& copy() const override;
            static std::shared_ptr<Node> createNode(const std::string& name, const std::any& value);
    };

    class HuffmanTree {
        private:
            typedef struct {
                int weight, parent, left, right;
            } Node;
            std::vector<Node> _nodes;

    };

}  // namespace Tree

#endif  // DATAFRAMEIMPL_TREE_H
