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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

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

Node* createNode(Type type, void* value);

LinkList* initList(Type type, int len, ...);

void* getElem(LinkList* list, int idx);

void insertElem(LinkList* list, int idx, void* value);

int locateElem(LinkList* list, void* value);

void removeElem(LinkList* list, int idx);

void modifyElem(LinkList* list, int idx, void* value);

typedef struct {
    void** base;
    void** top;
    int size;
} OrderStack;

OrderStack* initOrderStack();

void pushO(OrderStack* stack, void* value);

void* popO(OrderStack* stack);

void* getTopO(OrderStack* stack);

typedef struct {
    Node* head;
    int size;
} LinkStack;

LinkStack* initLinkStack();

void pushL(LinkStack* stack, void* value);

void* popL(LinkStack* stack);

void* getTopL(LinkStack* stack);

#endif  // DATAFRAMEIMPL_DFIMPL_H
