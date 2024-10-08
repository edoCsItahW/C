// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file exception.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/09/22 上午10:37
 * @brief 定义错误异常类
 * */

#ifndef VARLEX_EXCEPTION_H
#define VARLEX_EXCEPTION_H
#pragma once

#include <stdexcept>

/**
 * @namespace Err
 * @brief 定义错误异常类
 * @details 自定义异常类,更细致的分析错误.
 * */
namespace Err {
    /**
     * @class SyntaxError
     * @brief 语法错误异常类
     * @details 继承自std::runtime_error, 用于表示语法错误.
     * @extends std::runtime_error
     */
    class SyntaxError : public std::runtime_error {
        public:
            explicit SyntaxError(const std::string& message);
    };
}

#endif  // VARLEX_EXCEPTION_H
