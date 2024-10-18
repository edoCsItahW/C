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

#ifndef DATAFRAMEIMPL_DFIMPL_H
#define DATAFRAMEIMPL_DFIMPL_H
#pragma once

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef DLL_BUILD
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __declspec(dllimport)
#endif

#define MALLOC(type, size) (type*)malloc(size * sizeof(type))

#define ERROR(msg, ...)                                                                                                                                                                                \
    fprintf(stderr, msg, __VA_ARGS__);                                                                                                                                                                 \
    exit(EXIT_FAILURE)
#define ALLOC_ERROR ERROR("Memory allocation failed: line %d in <%s>", __LINE__, __FILE__)
#define ARGUMENT_ERROR(arg) ERROR("Argument error: line %d in <%s>: '%s'\n", __LINE__, __FILE__, #arg)
#define STACK_FULL_ERROR ERROR("Stack full: line %d in <%s>", __LINE__, __FILE__)
#define STACK_EMPTY_ERROR ERROR("Stack empty: line %d in <%s>", __LINE__, __FILE__)

#define CHECKMEM(ptr)                                                                                                                                                                                  \
    if (ptr == NULL) { ALLOC_ERROR; }

#define _REPLACE(_list, _idx, _var)                                                                                                                                                                  \
    Node* curr = _list->head;                                                                                                                                                                          \
    int j     = 0;                                                                                                                                                                                     \
    while (curr && j < _idx + _var) {                                                                                                                                                                  \
        if (curr->type == SINGLE) curr = curr->snode.next;                                                                                                                                             \
        else curr = curr->mnode.next;                                                                                                                                                                  \
        j++;                                                                                                                                                                                           \
    }                                                                                                                                                                                                  \
    if (!curr || j > _idx + _var) { ARGUMENT_ERROR(_idx); }                                                                                                                                            \

#define ORDER_STACK_SIZE 100

typedef enum { SINGLE, MULTI } Type;

typedef struct Node {
    Type type;
    union {
        struct singleNode {
                struct Node* next;
        } snode;
        struct multiNode {
                struct Node* prior;
                struct Node* next;
        } mnode;
    };
    void* value;
} Node;

typedef struct {
        Node* head;
        int size;
} LinkList;

EXPORT Node* createNode(Type type, void* value);

EXPORT LinkList* initList(Type type, int len, ...);

EXPORT void* getElem(LinkList* list, int idx);

EXPORT void insertElem(LinkList* list, int idx, void* value);

EXPORT int locateElem(LinkList* list, void* value);

EXPORT void removeElem(LinkList* list, int idx);

EXPORT void modifyElem(LinkList* list, int idx, void* value);

typedef struct {
        void** base;
        void** top;
        int size;
} OrderStack;

EXPORT OrderStack* initOrderStack();

EXPORT void pushO(OrderStack* stack, void* value);

EXPORT void* popO(OrderStack* stack);

EXPORT void* getTopO(OrderStack* stack);

typedef struct {
        Node* head;
        int size;
} LinkStack;

EXPORT LinkStack* initLinkStack();

EXPORT void pushL(LinkStack* stack, void* value);

EXPORT void* popL(LinkStack* stack);

EXPORT void* getTopL(LinkStack* stack);

#endif  // DATAFRAMEIMPL_DFIMPL_H
