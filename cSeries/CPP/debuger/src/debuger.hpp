// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file debuger.hpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/10 下午4:42
 * @brief 实现模板调试器类API
 * @copyright CC BY-NC-SA
 * */

#ifndef TEST_DEBUGER_HPP
#define TEST_DEBUGER_HPP
#pragma once

#include "debuger.h"

namespace debuger {
    template<Callable F>
    Debuger<F>::Debuger(F func, std::source_location loc)
        : _func(std::move(func))
        , _loc(loc) {}

    template<Callable F>
    template<typename... Args>
    auto Debuger<F>::operator()(Args &&...args) -> decltype(_func(std::forward<Args>(args)...)) {
        try {
            return _func(std::forward<Args>(args)...);
        } catch (const std::exception &e) {
            std::cerr << "Exception at " << _loc.file_name() << ":" << _loc.line() << " " << e.what() << std::endl;
        }
    }
}  // namespace debuger

#endif  // TEST_DEBUGER_HPP
