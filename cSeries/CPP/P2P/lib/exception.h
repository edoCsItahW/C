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
 * @date 2024/10/20 下午7:56
 * @brief
 * */

#ifndef P2PSERVER_EXCEPTION_H
#define P2PSERVER_EXCEPTION_H
#pragma once

#include <stdexcept>

class SocketError : public std::runtime_error {
public:
    SocketError(const std::string& msg) : std::runtime_error(msg) {}
};

#endif  // P2PSERVER_EXCEPTION_H
