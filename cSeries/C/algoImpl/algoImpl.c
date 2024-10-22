// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file algoImpl.c
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/19 下午8:45
 * @brief
 * @copyright CC BY-NC-SA
 * */

#include "algoImpl.h"

void swap(int* a, int* b) {
    int tmp = *a;
    *a      = *b;
    *b      = tmp;
}

int partition(int arr[], int left, int right) {
    int pivot = arr[right], i = left - 1;  // 选择右边的元素作为pivot
    for (int j = left; j < right; j++) if (arr[j] <= pivot) swap(&arr[++i], &arr[j]);
    swap(&arr[i + 1], &arr[right]);  // 交换pivot和分割点
    return i + 1;                    // 返回分割点的位置
}

void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int pi = partition(arr, left, right);  // 选择分割点
        quickSort(arr, left, pi - 1);          // 递归左边
        quickSort(arr, pi + 1, right);         // 递归右边
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = 0, flag = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) if (arr[j] > arr[j + 1]) {  // 每次选两个,比较,然后交换
                swap(&arr[j], &arr[j + 1]);
                flag = 1;
            }
        if (flag == 0) break;
    }
}

void shellSort(int arr[], int n) {  // 如[4, 2, 1, 0, 6, 5, 8, 3, 7, 9]
    for (int gap = n / 2; gap > 0; gap /= 2)  // gap = 5
        for (int i = gap; i < n; i++) {  // i = 5
            int tmp = arr[i], j;  // tmp = arr[5] = 5, j = ?
            for (j = i; j >= gap && arr[j - gap] > tmp; j -= gap) arr[j] = arr[j - gap];  // j = 5, (j: 5 >= gap: 5 && arr[5 - 5 = 0]: 4 > 5): False, arr[5] = arr[0](5去到0位置)
            arr[j] = tmp;  // (0去到5位置)
        }
}

void insertSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;  // key为待插入元素, j为待比较元素
        while (j >= 0 && arr[j] > key) {  // 从后向前比较, 找到比key小的元素,如果有则交换,到0则停止
            arr[j + 1] = arr[j];  // 被比较的元素后移
            j--;
        }
        arr[j + 1] = key;  // 插入key(由于j--了,所以j+1即为插入位置)
    }
}

void selectSort(int arr[], int n) {
    for (int i = 0, idx = 0; i < n - 1; i++, idx = i) {  // idx记录最小值索引
        for (int j = i + 1; j < n; j++) if (arr[j] < arr[idx]) idx = j;  // 找到比当前元素小的元素,然后再拿新元素和下一个元素比较,找到最小值索引
        if (idx != i) swap(&arr[i], &arr[idx]);  // 如果最小值索引不是当前索引,则将小的元素和当前元素交换
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;         // 初始化最大元素为根
    if (left < n && arr[left] > arr[largest]) largest = left;     // 找出左子节点最大值
    if (right < n && arr[right] > arr[largest]) largest = right;  // 找出右子节点最大值
    if (largest != i) {                                           // 如果最大值不是根节点
        swap(&arr[i], &arr[largest]);                             // 交换根节点和最大值
        heapify(arr, n, largest);                                 // 递归调整最大值
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);  // 构建最大堆
    for (int i = n - 1; i > 0; i--) {                         // 提取元素一个接一个地从堆中取出
        swap(&arr[0], &arr[i]);                               // 交换堆顶元素和最后一个元素
        heapify(arr, i, 0);                                   // 堆化剩余元素
    }
}

void merge(int arr[], int left, int mid, int right) {
    int i, j, k, n1 = mid - left + 1, n2 = right - mid, L[n1], R[n2];  // 左右数组长度和临时数组
    for (i = 0; i < n1; i++) L[i] = arr[left + i];                     // 拷贝数据到临时数组
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    i = 0; j = 0; k = left;  // 合并数组,初始化左右数组,初始索引合并后的数组
    while (i < n1 && j < n2) if (L[i] <= R[j]) arr[k++] = L[i++]; else arr[k++] = R[j++];
    while (i < n1) arr[k++] = L[i++];  // 合并左边剩余元素
    while (j < n2) arr[k++] = R[j++];  // 合并右边剩余元素
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // 选择中间元素作为分割点, 防止溢出
        mergeSort(arr, left, mid);            // 递归排序左边
        mergeSort(arr, mid + 1, right);       // 递归排序右边
        merge(arr, left, mid, right);         // 合并排序结果
    }
}

long long binPowR(int x, int n) {
    if (n == 0) return 1;
    long long res = binPowR(x, n / 2);
    if (n % 2 == 0) return res * res;
    else return res * res * x;
}

long long binPowI(int x, int n) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

int intLen(int num) {
    int count = 0;
    while (num &= (num - 1)) count++;
    return count;
}

bool repeat(int num) {
    int bitVec = 0, arr[32];
    for (int i = 0; i < intLen(num); i++) if (bitVec & (1 << arr[i])) return true; else bitVec |= (1 << arr[i]);
    return false;
}
