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

/** @def MALLOC
 * @brief 包装malloc函数,用于分配内存,简化操作
 * @details 可以将值写入内存,并获取指针
 * @param type 分配的内存类型
 * @param size 当当前类型由多个元素组成时,表示元素个数,当仅固定内存为指针时,应为1
 * @return 返回分配的内存指针
 * ## Example
 * @code
 * // 当仅固定内存为指针时
 * AStruct* ptr = (AStruct*)MALLOC(AStruct, 1);
 * // 当当前类型由多个元素组成时
 * int* arr = (int*)MALLOC(int, 10);
 * @endcode
 * @post 应跟随使用@ref CHECKMEM 宏检查分配是否成功
 * @warning 当内存不足,类型不匹配或者数组越界时,可能会分配失败
 * @see CHECKMEM
 * */
#define MALLOC(type, size) (type*)malloc(size * sizeof(type))

/** @def ERROR
 * @brief 打印错误信息并退出程序
 * @details 打印错误信息并退出程序,仅用于简化操作
 * @param msg 错误信息格式字符串
 * @param... 格式字符串参数
 * ## Example
 * @code
 * ERROR("Error: %s\n", "something wrong");
 * @endcode
 * @warning 当使用该宏抛出错误时,程序会终止运行,确保必要的资源已被释放
 * */
#define ERROR(msg, ...)                                                                                                                                                                                \
    fprintf(stderr, msg, __VA_ARGS__);                                                                                                                                                                 \
    exit(EXIT_FAILURE)

/** @def ALLOC_ERROR
 * @brief 打印内存分配失败信息并退出程序
 * @details 打印内存分配失败信息并退出程序,仅用于简化操作
 * ## Example
 * @code
 * // define a pointer variable
 * if (ptr == NULL) { ALLOC_ERROR; }
 * @endcode
 * @warning 当使用该宏抛出错误时,程序会终止运行,确保必要的资源已被释放
 * @exception ERROR 内存分配失败时,会打印错误信息并退出程序
 * @see ERROR
 * */
#define ALLOC_ERROR { ERROR("Memory allocation failed: line %d in <%s>", __LINE__, __FILE__); }

/** @def ARGUMENT_ERROR
 * @brief 打印参数错误信息并退出程序
 * @details 打印参数错误信息并退出程序,仅用于简化操作
 * @param arg 错误的参数名称
 * ## Example
 * @code
 * void func(void* arg) {
 *      if (ERROR_CONDITION) ARGUMENT_ERROR(arg)
 * }
 * @endcode
 * @warning 当使用该宏抛出错误时,程序会终止运行,确保必要的资源已被释放
 * @exception ERROR 参数错误时,会打印错误信息并退出程序
 * @see ERROR
 * */
#define ARGUMENT_ERROR(arg) { ERROR("Argument error: line %d in <%s>: '%s'\n", __LINE__, __FILE__, #arg); }

/** @def STACK_FULL_ERROR
 * @brief 打印栈满错误信息并退出程序
 * @details 打印栈满错误信息并退出程序,仅用于简化操作
 * ## Example
 * @code
 * if (stack->size == stack->capacity) STACK_FULL_ERROR
 * @endcode
 * @warning 当使用该宏抛出错误时,程序会终止运行,确保必要的资源已被释放
 * */
#define STACK_FULL_ERROR { ERROR("Stack full: line %d in <%s>", __LINE__, __FILE__); }

/** @def QUEUE_FULL_ERROR
 * @brief 打印队列满错误信息并退出程序
 * @details 打印队列满错误信息并退出程序,仅用于简化操作
 * ## Example
 * @code
 * if (queue->size == queue->capacity) QUEUE_FULL_ERROR
 * @endcode
 * @warning 当使用该宏抛出错误时,程序会终止运行,确保必要的资源已被释放
 * */
#define QUEUE_FULL_ERROR { ERROR("Queue full: line %d in <%s>", __LINE__, __FILE__); }

/** @def STACK_EMPTY_ERROR
 * @brief 打印栈空错误信息并退出程序
 * @details 打印栈空错误信息并退出程序,仅用于简化操作
 * ## Example
 * @code
 * if (stack->size == 0) STACK_EMPTY_ERROR
 * @endcode
 * @warning 当使用该宏抛出错误时,程序会终止运行,确保必要的资源已被释放
 * */
#define STACK_EMPTY_ERROR { ERROR("Stack empty: line %d in <%s>", __LINE__, __FILE__); }
#define QUEUE_EMPTY_ERROR { ERROR("Queue empty: line %d in <%s>", __LINE__, __FILE__); }

/** @def CHECKMEM
 * @brief 检查内存是否分配成功
 * @details 检查内存是否分配成功,仅用于简化操作
 * @param ptr 待检查的内存指针
 * ## Example
 * @code
 * // define a pointer variable
 * Type* ptr = MALLOC(Type, 10);
 * // check if allocation is successful
 * CHECKMEM(ptr);
 * @endcode
 * @pre 一般搭配@ref MALLOC 使用,用于检查分配是否成功
 * @warning 当内存分配失败时,程序会终止运行,确保必要的资源已被释放
 */
#define CHECKMEM(ptr)                                                                                                                                                                                  \
    if (ptr == NULL) { ALLOC_ERROR; }

#define _REPLACE(_list, _idx, _var)                                                                                                                                                                    \
    Node* curr = _list->head;                                                                                                                                                                          \
    int j      = 0;                                                                                                                                                                                    \
    while (curr && j < _idx + _var) {                                                                                                                                                                  \
        if (curr->type == SINGLE)                                                                                                                                                                      \
            curr = curr->snode.next;                                                                                                                                                                   \
        else                                                                                                                                                                                           \
            curr = curr->mnode.next;                                                                                                                                                                   \
        j++;                                                                                                                                                                                           \
    }                                                                                                                                                                                                  \
    if (!curr || j > _idx + _var) { ARGUMENT_ERROR(_idx); }

/** @enum Type
 * @brief 节点类型枚举
 * @details 节点类型枚举,用于区分单节点和多节点
 * */
typedef enum {
    SINGLE,  ///< 单节点
    MULTI   ///< 多节点
} Type;

/** @struct Node
 * @brief 节点结构体
 * @details 节点结构体,用于存储节点类型,节点值,节点指针等信息
 * */
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

// -------------------------- Order Stack --------------------------

typedef struct {
    void** base;
    void** top;
    int size;
} S_OrderStack;

S_OrderStack* initOrderStack();

void pushOS(S_OrderStack* stack, void* value);

void* popOS(S_OrderStack* stack);

void* getTopOS(S_OrderStack* stack);

typedef struct {
    S_OrderStack* (*init)();
    void (*push)(S_OrderStack* stack, void* value);
    void* (*pop)(S_OrderStack* stack);
    void* (*getTop)(S_OrderStack* stack);
} M_OrderStack;

extern M_OrderStack OrderStack;

// -------------------------- Link Stack --------------------------

typedef struct {
    Node* head;
    int size;
} S_LinkStack;

S_LinkStack* initLinkStack();

void pushLS(S_LinkStack* stack, void* value);

void* popLS(S_LinkStack* stack);

void* getTopLS(S_LinkStack* stack);

typedef struct {
    S_LinkStack* (*init)();
    void (*push)(S_LinkStack* stack, void* value);
    void* (*pop)(S_LinkStack* stack);
    void* (*getTop)(S_LinkStack* stack);
} M_LinkStack;

extern M_LinkStack LinkStack;

// -------------------------- Order Queue --------------------------

typedef struct {
    void** base;
    int font;
    int rear;
} S_OrderQueue;

S_OrderQueue* initOrderQueue();

int sizeOQ(S_OrderQueue* queue);

void enqueueOQ(S_OrderQueue* queue, void* value);

void* dequeueOQ(S_OrderQueue* queue);

void* getFrontOQ(S_OrderQueue* queue);

typedef struct {
    S_OrderQueue* (*init)();
    int (*size)(S_OrderQueue* queue);
    void (*enqueue)(S_OrderQueue* queue, void* value);
    void* (*dequeue)(S_OrderQueue* queue);
    void* (*getFront)(S_OrderQueue* queue);
} M_OrderQueue;

extern M_OrderQueue OrderQueue;

// -------------------------- Link Queue --------------------------

typedef struct {
    Node* font;
    Node* rear;
} S_LinkQueue;

S_LinkQueue* initLinkQueue();

int sizeLQ(S_LinkQueue* queue);

void enqueueLQ(S_LinkQueue* queue, void* value);

void* dequeueLQ(S_LinkQueue* queue);

void* getFrontLQ(S_LinkQueue* queue);

typedef struct {
    S_LinkQueue* (*init)();
    int (*size)(S_LinkQueue* queue);
    void (*enqueue)(S_LinkQueue* queue, void* value);
    void* (*dequeue)(S_LinkQueue* queue);
    void* (*getFront)(S_LinkQueue* queue);
} M_LinkQueue;

extern M_LinkQueue LinkQueue;

// -------------------------- Tree ---------------------------------

typedef struct NodeT {
    int value;
    struct NodeT* left;
    struct NodeT* right;
} NodeT;

NodeT* createNodeT(int value);

#endif  // DATAFRAMEIMPL_DFIMPL_H
