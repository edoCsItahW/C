// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// -------------------------<edocsitahw>----------------------------
// ???????: 2024/05/08 ????7:51
// ????????: test
// ??????: utf-8
// ???:
// -------------------------<edocsitahw>----------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define print(value) _Generic((value), int: printf("%d", value), char*: printf("%d", value))

void** insertSort(void** arr, int size, int (*cmp)(void*, void*)) {
    for (int i = 1; i < size; i++) {
        void* key = arr[i];
        int j     = i - 1;
        while (j >= 0 && cmp(arr[j], arr[i]) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return arr;
}



char* intToBinary(int data) {
    // 计算二进制表示的最大长度
    int len      = sizeof(int) * 8;  // 32位整数的最大长度
    char* binary = (char*)malloc((len + 1) * sizeof(char));
    if (binary == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    // 初始化字符串
    memset(binary, '0', len);
    binary[len] = '\0';

    // 计算二进制表示
    int index = len - 1;
    while (data > 0) {
        binary[index--] = (data % 2) + '0';
        data /= 2;
    }

    // 去除前导零
    char* result = binary;
    while (*result == '0' && *(result + 1) != '\0') result++;

    return result;
}

int stoi(const char* str) {
    int res = 0;
    for (int i = 0; i < strlen(str); i++) res += (str[i] - 48) * (int)pow(10, (int)strlen(str) - i - 1);
    return res;
}

typedef struct {
        char** list;
        int size;
} List;

List* parser(const char* date) {
    List* res = (List*)malloc(sizeof(List));
    res->size = 0;
    res->list = (char**)malloc(sizeof(char*));

    char* tmp  = (char*)malloc(sizeof(char));
    int tmpLen = 1;
    int count  = 0;

    for (int i = 0; i < strlen(date); i++) {
        if (date[i] == '-') {
        label:

            tmp[tmpLen - 1]      = '\0';
            res->list            = (char**)realloc(res->list, (res->size + 1) * sizeof(char*));
            res->list[res->size] = (char*)malloc((tmpLen + 1) * sizeof(char));
            strcpy(res->list[res->size++], tmp);
            free(tmp);
            if (count < 1) {
                tmp    = (char*)malloc(sizeof(char));
                tmpLen = 1;
            }
        } else {
            tmp = (char*)realloc(tmp, (tmpLen + 1) * sizeof(char));
            if (tmp == NULL) {
                fprintf(stderr, "Memory allocation failed!\n");
                exit(1);
            }
            tmp[tmpLen - 1] = date[i];
            tmpLen++;
        }
    }
    if (count < 1) {
        count++;
        goto label;
    }

    return res;
}

char* cat(char** list, int size) {
    char* res = (char*)malloc(sizeof(char));

    for (int i = 0; i < size; i++) strcat(res, intToBinary(stoi(list[i])));

    return res;
}

int compare(void* x, void* y) {
    return ((int)x > (int)y) - ((int)x < (int)y);
}

int main() {
    int a[] = {4, 2, 6, 1, 10};
    insertSort(a, 5, compare);

    for (int i = 0; i < 5; i++) printf("%d\n", (int)a[i]);

    return 0;
}
