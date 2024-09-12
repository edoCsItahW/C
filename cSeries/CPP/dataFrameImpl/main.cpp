// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: test
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/09/06 上午10:02
 * @Commend:
 *******************************************************/

#include "algo/algo.h"
#include "list/list.h"
#include "tree/tree.h"

// OrderList
void OrderListTest() {
    using namespace List;
    OrderList<int> ol(5);
    for (int i = 0; i < 5; i++) ol.insertElem(i, i);
    for (int i = 0; i < ol.size(); i++) std::cout << ol.getElem(i) << " ";
    std::cout << std::endl;
    std::cout << "find 3: " << ol.locateElem(3) << std::endl;
}

// LinkList
void LinkListTest() {
    using namespace List;
    LinkList<int> ll;
    for (int i = 0; i < 5; i++) ll.insertElem(i, i);
    for (int i = 0; i < ll.size(); i++) std::cout << ll.getElem(i) << " ";
    std::cout << std::endl;
    std::cout << "find 3: " << ll.locateElem(3) << std::endl;
}

// BinaryTree
void BinaryTreeTest() {
    using namespace Tree;

    std::map<std::string, std::any> data{
        {"data1", "some data"},
        {"data2", 123        }
    };
    std::map<std::string, std::any> data1{
        {"name", data},
        {"age",  data}
    };

    auto tree = BinaryTree(data1);

    std::cout << "Deep: " << tree.deep() << std::endl;

    std::cout << "Data: " << tree.root()->left->right->name << std::endl;
}

// Algo
void BinSearchTest() {
    using namespace Algo;
    std::vector<std::string> vec = {"apple", "banana", "orange", "pear", "grape"};

    std::cout << "find 5: " << binSearch(vec, std::string("orange"), [](const std::string& left, const std::string& right) {
        return left[0] < right[0];
    }) << std::endl;
}

// test
int main() {
    BinSearchTest();

    return 0;
}
