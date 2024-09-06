// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: szbz
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/31 下午4:48
 * @Commend:
 *******************************************************/

#ifndef SZBZ_ENUMMAP_H
#define SZBZ_ENUMMAP_H
#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

template<typename T, class En>
/** @brief 枚举映射
     *
     * @tparam T 目标列表包含数据类型
     * @tparam En 支持枚举类型
     * */
class Map {
    private:
        std::vector<T> _vec;  // 目标列表

    public:
        /** @brief 构造函数
             *
             * @param vec 目标列表
             * */
        explicit Map(std::vector<T>& vec)
            : _vec(vec) {}

        /** @brief 重载 [] 操作符
         *
         * @param key 枚举类型
         * @return const T& 目标列表中对应枚举值的引用
         * */
        const T& operator[](En key) const { return _vec[static_cast<int>(key)]; }

        /** @brief 重载 [] 操作符
         *
         * @param key 整数索引
         * @return const T& 目标列表中对应索引值的引用
         * */
        const T& operator[](int key) const { return _vec[key]; }

        const T& operator[](size_t key) const { return _vec[key]; }

        [[nodiscard]] int index(const T& value) const {
            auto it = std::find(_vec.begin(), _vec.end(), value);
            if (it == _vec.end()) {
                throw std::out_of_range("key not found");
                }
            return std::distance(_vec.begin(), it);
        }
};

#endif  // SZBZ_ENUMMAP_H
