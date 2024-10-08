// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File nodeName: bridging
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/09/11 下午10:24
 * @Commend:
 *******************************************************/

#ifndef BRIDGING_TEST_H
#define BRIDGING_TEST_H
#pragma once

#include <cstdio>

/** @brief 交换两个整数的值
 *
 * @param a 第一个整数
 * @param b 第二个整数
 * */
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/** @brief 快速排序
 *
 * @details 快速排序的分割
 *
 * @param arr 待排序数组
 * @param left 左边界
 * @param right 右边界
 * @return 分割点的位置
 * */
int partition(int arr[], int left, int right) {
    int pivot = arr[right];  // 选择右边的元素作为pivot
    int i = left - 1;  // 左边的指针
    for (int j = left; j < right; j++) if (arr[j] <= pivot) swap(&arr[++i], &arr[j]);
    swap(&arr[i + 1], &arr[right]);  // 交换pivot和分割点
    return i + 1;  // 返回分割点的位置
}

/** @brief 快速排序
 *
 * @param arr 待排序数组
 * @param left 左边界
 * @param right 右边界
 * */
void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int pi = partition(arr, left, right);  // 选择分割点
        quickSort(arr, left, pi - 1);  // 递归左边
        quickSort(arr, pi + 1, right);  // 递归右边
    }
}

#endif  // BRIDGING_TEST_H
