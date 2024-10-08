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
 * @Date: 2024/09/13 上午10:15
 * @Commend:
 *******************************************************/

#include "dfImpl.h"
//#define NDEBUG

#define MALLOC(type, size) (type*)malloc(size * sizeof(type))

#define ERROR(msg, ...) fprintf(stderr, msg, __VA_ARGS__); exit(EXIT_FAILURE)
#define ALLOC_ERROR ERROR("Memory allocation failed: line %d in <%s>", __LINE__, __FILE__)
#define ARGUMENT_ERROR(arg) ERROR("Argument error: line %d in <%s>: '%s'\n", __LINE__, __FILE__, #arg)
#define STACK_FULL_ERROR ERROR("Stack full: line %d in <%s>", __LINE__, __FILE__)
#define STACK_EMPTY_ERROR ERROR("Stack empty: line %d in <%s>", __LINE__, __FILE__)

#define CHECKMEM(ptr)                   \
    if (ptr == NULL) { ALLOC_ERROR; }

#define _REPLACE(_list, _idx, _var)                                                                                                                                                                          \
    auto curr = _list->head;                                                                                                                                                                           \
    int j     = 0;                                                                                                                                                                                     \
    while (curr && j < _idx + _var) {                                                                                                                                                                         \
        if (curr->type == SINGLE) curr = curr->snode.next;                                                                                                                                                                   \
        else curr = curr->mnode.next;                                                                                                                                                                   \
        j++;                                                                                                                                                                                           \
    }                                                                                                                                                                                                  \
    if (!curr || j > _idx + _var) { ARGUMENT_ERROR(_idx); }

#define ORDER_STACK_SIZE 100

Node* createNode(Type type, void* value) {
    Node* node = MALLOC(Node, 1);
    CHECKMEM(node)
    node->type  = type;
    node->value = value;
    return node;
}

LinkList* initList(Type type, int len, ...) {
    LinkList* list = MALLOC(LinkList, 1);
    CHECKMEM(list)
    list->size = 0;
    list->head = NULL;
    va_list args;
    va_start(args, len);
    Node* prevNode = NULL;
    for (int i = 0; i < len; i++) {
        void* value = va_arg(args, void*);
        Node* newNode = createNode(type, value);
        if (list->head == NULL) list->head = newNode;
        else {
            if (type == SINGLE) prevNode->snode.next = newNode;
            else {
                newNode->mnode.prior = prevNode;
                prevNode->mnode.next = newNode;
            }
        }
        prevNode = newNode;
        list->size++;
    }
    va_end(args);
    return list;
}

void* getElem(LinkList* list, int idx) {
    _REPLACE(list, idx, 0)
    return curr->value;
}

void insertElem(LinkList* list, int idx, void* value) {
    _REPLACE(list, idx, -1)
    auto newNode = createNode(curr->type, value);
    if (curr->type == SINGLE) {
        newNode->snode.next = curr->snode.next;
        curr->snode.next    = newNode;
    }
    else {
        newNode->mnode.next  = curr->mnode.next;
        newNode->mnode.prior = curr;
        curr->mnode.next     = newNode;
        if (newNode->mnode.next) newNode->mnode.next->mnode.prior = newNode;
    }
    list->size++;
}

int locateElem(LinkList* list, void* value) {
    auto curr = list->head;
    int idx   = 0;
    while (curr && curr->value != value) {
        if (curr->type == SINGLE) curr = curr->snode.next;
        else curr = curr->mnode.next;
        idx++;
    }
    return curr ? idx : -1;
}

void removeElem(LinkList* list, int idx) {
    _REPLACE(list, idx, -1)
    auto next = curr->type == SINGLE ? curr->snode.next : curr->mnode.next;
    if (curr->type == SINGLE) curr->snode.next = next;
    else {
        curr->mnode.next->mnode.prior = curr->mnode.prior;
        if (curr->mnode.prior) curr->mnode.prior->mnode.next = curr->mnode.next;
        else list->head = curr->mnode.next;
    }
    list->size--;
}

void modifyElem(LinkList* list, int idx, void* value) {
    _REPLACE(list, idx, 0)
    curr->value = value;
}

OrderStack* initOrderStack() {
    OrderStack* stack = MALLOC(OrderStack, 1);
    CHECKMEM(stack)
    stack->base = MALLOC(void*, ORDER_STACK_SIZE);
    CHECKMEM(stack->base)
    stack->top = stack->base;
    stack->size = ORDER_STACK_SIZE;
    return stack;
}

void pushO(OrderStack* stack, void* value) {
    if (stack->top - stack->base == ORDER_STACK_SIZE) { STACK_FULL_ERROR; }
    *stack->top++ = value;
}

void* popO(OrderStack* stack) {
    if (stack->top == stack->base) { STACK_FULL_ERROR; }
    return *(--stack->top);
}

void* getTopO(OrderStack* stack) {
    if (stack->top != stack->base) return *(stack->top - 1);
    return NULL;
}

LinkStack* initLinkStack() {
    LinkStack* stack = MALLOC(LinkStack, 1);
    CHECKMEM(stack)
    stack->head = NULL;
    stack->size = 0;
    return stack;
}

void pushL(LinkStack* stack, void* value) {
    auto node = createNode(SINGLE, value);
    node->snode.next = stack->head;
    stack->head      = node;
    stack->size++;
}

void* popL(LinkStack* stack) {
    if (stack->head == NULL) { STACK_EMPTY_ERROR; }
    auto node = stack->head;
    stack->head = node->snode.next;
    stack->size--;
    return node->value;
}

void* getTopL(LinkStack* stack) {
    if (stack->head != NULL) return stack->head->value;
    return NULL;
}
