// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file node.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/09/22 下午8:36
 * @brief node.h的实现文件，定义了AST、STMT、Expression、Expr等类
 * @copyright CC BY-NC-SA
 * */

#include "node.h"

// ======================= AST Class ====================

AST::ASTNode::ASTNode() : nodeName("AST") {}

// ======================= STMT Class ===================

AST::STMT::STMT(std::vector<std::unique_ptr<AST::ASTNode>> _body): body(std::move(_body)) { nodeName = "STMT"; }

// ======================= Expression Class =============

// ======================= Expr Class ===================

