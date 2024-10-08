// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file node.tpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/09/23 下午1:23
 * @brief 需要推导的函数定义
 * @copyright CC BY-NC-SA
 * */

#ifndef VARLEX_NODE_CUH
#define VARLEX_NODE_CUH
#pragma once

#include "node.h"

std::string AST::ASTNode::toString(auto &&...args) const {
    std::ostringstream oss;
    oss << nodeName << "(";
    if constexpr (sizeof...(args) > 0) ((oss << args << ", "), ...);
    oss << ")";
    return oss.str();
}

std::string AST::STMT::toString(auto &&...args) const {
    return AST::ASTNode::toString(std::format("{}: {}", "body", body.size()), std::forward<decltype(args)>(args)...);
}

template<ConstType T>
AST::Constant<T>::Constant(T value, TokenType type) : Expression(), value(value), type(type) { nodeName = "Constant"; }

#endif  // VARLEX_NODE_CUH
