/**
 * @file main.c
 * @author edocsitahw
 * @version 1.1
 * @date 2024/09/26 ����9:07
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
    int data;                // �ڵ�����
    struct TreeNode* left;   // ���ӽڵ�
    struct TreeNode* right;  // ���ӽڵ�
} TreeNode;

// �����½ڵ�
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];  // �洢�ڵ�����
    int size;            // ��ǰ���Ľڵ���
} ArrayTree;

// ��ʼ����
void initTree(ArrayTree* tree) {
    tree->size = 0;
}

// ��ӽڵ�
void addNode(ArrayTree* tree, int data) {
    if (tree->size < MAX_SIZE) {
        tree->data[tree->size++] = data;
    } else {
        printf("����������������½ڵ�\n");
    }
}

typedef struct {
    int data[MAX_SIZE];   // �洢�ڵ�����
    int parent[MAX_SIZE]; // �洢ÿ���ڵ�ĸ��ڵ��±�
    int size;             // ��ǰ���Ľڵ���
} ParentChildTree;

// ��Ӹ��ڵ�
void addRootNode(ParentChildTree* tree, int data) {
    tree->data[tree->size] = data;
    tree->parent[tree->size++] = -1; // ���ڵ�û�и��ڵ�
}

// ����ӽڵ�
void addChildNode(ParentChildTree* tree, int parentIndex, int data) {
    if (tree->size < MAX_SIZE) {
        tree->data[tree->size] = data;
        tree->parent[tree->size++] = parentIndex; // ��ǰ�ڵ�ĸ��ڵ��±�
    }
    else printf("����������������½ڵ�\n");
}

