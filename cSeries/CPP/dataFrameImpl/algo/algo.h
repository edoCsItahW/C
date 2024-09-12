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
 * @Date: 2024/09/09 下午8:06
 * @Commend:
 *******************************************************/

#ifndef DATAFRAMEIMPL_ALGO_H
#define DATAFRAMEIMPL_ALGO_H
#pragma once

#include <iostream>
#include <vector>
#include <functional>


namespace Algo {
    template<typename F, typename T>
    concept Comparator = requires(F f, T left, T right) {
        { f(left, right) } -> std::convertible_to<bool>;
    };

    template<typename T, Comparator<T> Cmp>
    /**
     * @brief 二分查找算法
     *
     * @tparam T 数据类型
     * @param arr 待查找的数组
     * @param key 待查找的关键字
     * @return int 关键字在数组中的位置
     * */
    int binSearch(std::vector<T> arr, T key, Cmp cmp = nullptr) {
        int left = 0, right = arr.size() - 1, mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (arr[mid] == key) return mid;
            else if (cmp == nullptr ? (arr[mid] < key) : cmp(arr[mid], key)) right = mid - 1;
            else left = mid + 1;
        }
        return -1;
    }
}

#endif  // DATAFRAMEIMPL_ALGO_H
