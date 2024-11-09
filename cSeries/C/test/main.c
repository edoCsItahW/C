/**
 * @file main.c
 * @author edocsitahw
 * @version 1.1
 * @date 2024/09/26 上午9:07
 * @brief
 * @copyright CC BY-NC-SA 2024. All rights reserved.
 **/
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef enum { ATOM, LIST } NodeType;
//
//typedef struct GListNode {
//    NodeType type;
//
//    union {
//        int atom;
//        struct GListNode* head;
//    };
//    struct GListNode* next;
//} GListNode;
//
//GListNode* createAtomNode(int value) {
//    GListNode* newNode = (GListNode*)malloc(sizeof(GListNode));
//    newNode->type      = ATOM;
//    newNode->atom      = value;
//    newNode->next      = NULL;
//    return newNode;
//}
//
//GListNode* createListNode(GListNode* head) {
//    GListNode* newNode = (GListNode*)malloc(sizeof(GListNode));
//    newNode->type      = LIST;
//    newNode->head      = head;
//    newNode->next      = NULL;
//    return newNode;
//}
//
//void insertEnd(GListNode** list, GListNode* newNode) {
//    if (*list == NULL) {
//        *list = newNode;
//    } else {
//        GListNode* temp = *list;
//        while (temp->next != NULL) temp = temp->next;
//        temp->next = newNode;
//    }
//}
//
//void printGList(GListNode* list) {
//    printf("(");
//    while (list != NULL) {
//        if (list->type == ATOM)
//            printf("%d", list->atom);
//        else
//            printGList(list->head);
//        list = list->next;
//        if (list != NULL) printf(", ");
//    }
//    printf(")");
//}
//
//void freeGList(GListNode* list) {
//    while (list != NULL) {
//        GListNode* temp = list;
//        list            = list->next;
//        if (temp->type == LIST) freeGList(temp->head);
//        free(temp);
//    }
//}
//
//int main() {
//    GListNode* gList = NULL;
//
//    GListNode* subList1 = createListNode(createAtomNode(1));
//    insertEnd(&subList1, createAtomNode(2));
//    insertEnd(&gList, createListNode(subList1));
//
//    insertEnd(&gList, createAtomNode(3));
//
//    GListNode* subList2   = createListNode(createAtomNode(4));
//    GListNode* subSubList = createListNode(createAtomNode(5));
//    insertEnd(&subSubList, createAtomNode(6));
//    insertEnd(&subList2, subSubList);
//    insertEnd(&gList, createListNode(subList2));
//
//    printGList(gList);
//    printf("\n");
//
//    freeGList(gList);
//
//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;                // 节点数据
    struct TreeNode* left;   // 左子节点
    struct TreeNode* right;  // 右子节点
} TreeNode;

// 创建新节点
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];  // 存储节点数据
    int size;            // 当前树的节点数
} ArrayTree;

// 初始化树
void initTree(ArrayTree* tree) {
    tree->size = 0;
}

// 添加节点
void addNode(ArrayTree* tree, int data) {
    if (tree->size < MAX_SIZE) {
        tree->data[tree->size++] = data;
    } else {
        printf("树已满，不能添加新节点\n");
    }
}

typedef struct {
    int data[MAX_SIZE];   // 存储节点数据
    int parent[MAX_SIZE]; // 存储每个节点的父节点下标
    int size;             // 当前树的节点数
} ParentChildTree;

// 添加根节点
void addRootNode(ParentChildTree* tree, int data) {
    tree->data[tree->size] = data;
    tree->parent[tree->size++] = -1; // 根节点没有父节点
}

// 添加子节点
void addChildNode(ParentChildTree* tree, int parentIndex, int data) {
    if (tree->size < MAX_SIZE) {
        tree->data[tree->size] = data;
        tree->parent[tree->size++] = parentIndex; // 当前节点的父节点下标
    }
    else printf("树已满，不能添加新节点\n");
}

