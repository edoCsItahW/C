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
 * @Date: 2024/09/13 上午10:17
 * @Commend:
 *******************************************************/

#include "dfImpl.h"

void test_SingleLinkList() {
    LinkList* list = initList(SINGLE, 2, 1, 2);
    auto res = getElem(list, 1);
    assert((int)res == 2);
    printf("The element at index 1 is: %d\n", (int)res);

    insertElem(list, 2, (void*)3);
    res = getElem(list, 2);
    assert((int)res == 3);
    printf("The element at index 2 is: %d\n", (int)res);

    int pos = locateElem(list, (void*)2);
    assert(pos == 1);
    printf("Find 2 in index: %d\n", pos);

    modifyElem(list, 2, (void*)4);
    res = getElem(list, 2);
    assert((int)res == 4);
    printf("The element at index 2 is: %d\n", (int)res);

    removeElem(list, 1);
    res = getElem(list, 1);
    assert((int)res == 2);
    printf("The element at index 1 is: %d\n", (int)res);
}

void test_OrderStack() {
    printf("Testing OrderStack...\n");
    OrderStack* stack = initOrderStack();
    pushO(stack, (void*)1);
    pushO(stack, (void*)2);
    pushO(stack, (void*)3);

    void* res = popO(stack);
    assert((int)res == 3);
    printf("The top element is: %d\n", (int)res);

    res = getTopO(stack);
    assert((int)res == 2);
    printf("The top element is: %d\n", (int)res);
}

void test_LinkStack() {
    printf("Testing LinkStack...\n");
    LinkStack* stack = initLinkStack();
    pushL(stack, (void*)1);
    pushL(stack, (void*)2);
    pushL(stack, (void*)3);

    void* res = popL(stack);
    assert((int)res == 3);
    printf("The top element is: %d\n", (int)res);

    res = getTopL(stack);
    assert((int)res == 2);
    printf("The top element is: %d\n", (int)res);
}

int main() {
    test_OrderStack();
    test_LinkStack();
    return 0;
}
