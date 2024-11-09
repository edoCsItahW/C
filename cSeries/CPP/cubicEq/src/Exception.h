// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file Exception.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/11/07 下午6:46
 * @brief
 * */
#ifndef CUBICEQ_EXCEPTION_H
#define CUBICEQ_EXCEPTION_H
#pragma once

#include <stdexcept>

class Exception : public std::runtime_error {
public:
    Exception(const std::string& message)
        : std::runtime_error(message) {}
};

class TypeError : public Exception {
public:
    TypeError(const std::string& message)
        : Exception(message) {}
};

#endif  // CUBICEQ_EXCEPTION_H
