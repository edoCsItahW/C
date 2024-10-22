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
    template<typename R, typename... Args>
    Debuger<R, Args...>::Debuger(Debuger::F func, std::source_location loc)
        : _func(std::move(func))
        , _loc(loc) {}

    template<typename R, typename... Args>
    R Debuger<R, Args...>::operator()(Args &&...args) {
        try {
            return _func(std::forward<Args>(args)...);
        }
        catch (const std::exception &e) {
            if constexpr (std::is_same_v<void, R>) {
                // 如果返回值是void,则什么都不做
            }
            else {
                // 调试器并不中断程序的运行
                std::cerr << "Exception at " << _loc.file_name() << ":" << _loc.line() << " " << e.what() << std::endl;
                return R{};
            }
        }
    }
}  // namespace debuger

#endif  // TEST_DEBUGER_HPP

//    template<Callable F>
//    Debuger<F>::Debuger(F func, std::source_location loc)
//        : _func(std::move(func))
//        , _loc(loc) {}
//
//    template<Callable F>
//    template<typename... Args>
//    auto Debuger<F>::operator()(Args &&...args) -> decltype(auto) {  // std::declval<F>(std::forward<Args>(args)...)
//        using R = decltype(_func(std::forward<Args>(args)...));
//        try {
//            return _func(std::forward<Args>(args)...);
//        }
//        catch (const std::exception &e) {
//            if constexpr (std::is_same_v<void, R>) {}
//            else {
//                std::cerr << "Exception at " << _loc.file_name() << ":" << _loc.line() << " " << e.what() << std::endl;
//                return R{};
//            }
//        }
//    }
