// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file vdb.h
 * @author: edocsitahw
 * @version 1.1
 * @date 2024/09/22 上午10:36
 * @brief 为VarLex解释器提供小型调试工具
 * @copyright CC BY-NC-SA
 * */

#ifndef VARLEX_VDB_H
#define VARLEX_VDB_H
#pragma once

#include <format>
#include <functional>
#include <iostream>
#include <source_location>

/**
 * @namespace VDB
 * @brief VarLex调试工具
 * @details 该命名空间提供VarLex调试工具，包括Try类和dbg函数。
 * */
namespace VDB {
    class Try {
        private:
            bool debug;
            explicit Try(bool debug);
            explicit Try();
            ~Try();

        public:
            static Try& getInstance(bool debug = false);
            Try(const Try&)            = delete;
            void operator=(const Try&) = delete;
            template<typename F>
            auto operator()(F fn, std::source_location loc = std::source_location::current());
    };

    extern Try& try_;

    template<typename F>
    auto dbg(F fn, bool debug = false, std::source_location loc = std::source_location::current());
}  // namespace VDB

#endif  // VARLEX_VDB_H
