// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file debuger.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/10 下午4:42
 * @brief 调试器API头文件
 * @copyright Copyright (c) 2024. All rights reserved.
 * */

#ifndef TEST_DEBUGER_H
#define TEST_DEBUGER_H
#pragma once

#include <iostream>
#include <utility>
#include <source_location>

namespace debuger {
    template <typename T>
    concept Callable = std::is_invocable_v<T>;

    template<Callable F>
    class Debuger {
    public:
        explicit Debuger(F func, std::source_location loc = std::source_location::current());

        template<typename... Args>
        auto operator()(Args&&... args) -> decltype(_func(std::forward<Args>(args)...));

        template<typename U>
        void test(U&& u);

        private:
         F _func;
         std::source_location _loc;
    };

}  // namespace debuger

#include "debuger.hpp"

#endif  // TEST_DEBUGER_H
