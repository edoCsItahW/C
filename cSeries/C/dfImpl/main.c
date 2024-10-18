// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file main.c
 * @author edocsitahw
 * @version 1.1
 * @date 2024/09/13 上午10:17
 * @brief
 * @copyright CC BY-NC-SA
 * */

#include "src/st/dfImpl.h"
#include <string.h>

void test_SingleLinkList() {
    LinkList* list = initList(SINGLE, 2, 1, 2);
    void* res       = getElem(list, 1);
    assert(*(int*)&res == 2);
    printf("The element at index 1 is: %d\n", *(int*)&res);

    insertElem(list, 2, (void*)3);
    res = getElem(list, 2);
    assert(*(int*)&res == 3);
    printf("The element at index 2 is: %d\n", *(int*)&res);

    int pos = locateElem(list, (void*)2);
    assert(pos == 1);
    printf("Find 2 in index: %d\n", pos);

    modifyElem(list, 2, (void*)4);
    res = getElem(list, 2);
    assert(*(int*)&res == 4);
    printf("The element at index 2 is: %d\n", *(int*)&res);

    removeElem(list, 1);
    res = getElem(list, 1);
    assert(*(int*)&res == 2);
    printf("The element at index 1 is: %d\n", *(int*)&res);
}

void test_OrderStack() {
    printf("Testing OrderStack...\n");
    S_OrderStack* stack = OrderStack.init();
    OrderStack.push(stack, (void*)1);
    OrderStack.push(stack, (void*)2);
    OrderStack.push(stack, (void*)3);

    void* res = OrderStack.pop(stack);
    assert(*(int*)&res == 3);
    printf("The top element is: %d\n", *(int*)&res);

    res = OrderStack.getTop(stack);
    assert(*(int*)&res == 2);
    printf("The top element is: %d\n", *(int*)&res);
}

void test_LinkStack() {
    printf("Testing LinkStack...\n");
    S_LinkStack* stack = LinkStack.init();
    LinkStack.push(stack, (void*)1);
    LinkStack.push(stack, (void*)2);
    LinkStack.push(stack, (void*)3);

    void* res = LinkStack.pop(stack);
    assert(*(int*)&res == 3);
    printf("The top element is: %d\n", *(int*)&res);

    res = LinkStack.getTop(stack);
    assert(*(int*)&res == 2);
    printf("The top element is: %d\n", *(int*)&res);
}

char* slice(const char* str, int start, int end) {
    char* res = MALLOC(char, end - start + 1);
    CHECKMEM(res)
    strncpy(res, str + start, end - start);
    res[end - start] = '\0';
    return res;
}

void test_parenthesisMatch() {
    printf("Testing parenthesisMatch...\n");

    const char* text = "f t((x: number) => ((x + 1) * 2) % 3 == 0)";

    S_LinkStack* stack = LinkStack.init();

    int col = 0;
    while (text[col] != '\0') {
        if (text[col] == '(') {
            int* index = MALLOC(int, 1);
            *index     = col;
            LinkStack.push(stack, (void*)index);
        } else if (text[col] == ')') {
            if (stack->head == NULL) { ERROR("Unmatched parenthesis: line %d in <%s>", __LINE__, __FILE__); }
            else {
                int* index = (int*)LinkStack.pop(stack);
                printf("%s\n", slice(text, *index + 1, col));
            }
        }
        col++;
    }
}

void test_OrderQueue() {
    printf("Testing OrderQueue...\n");
    S_OrderQueue* queue = OrderQueue.init();
    OrderQueue.enqueue(queue, (void*)1);
    OrderQueue.enqueue(queue, (void*)2);

    void* res = OrderQueue.dequeue(queue);
    assert(*(int*)&res == 1);
    printf("The first element is: %d\n", *(int*)&res);

    res = OrderQueue.getFront(queue);
    assert(*(int*)&res == 2);
    printf("The first element is: %d\n", *(int*)&res);
}

int main() {
    test_OrderQueue();
    return 0;
}
