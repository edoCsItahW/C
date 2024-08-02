// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: REACTIVE
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/31 下午12:22
 * @Commend:
 *******************************************************/

#ifndef REACTIVE_BASETYPE_H
#define REACTIVE_BASETYPE_H
#include <map>
#include <unordered_map>
#include <variant>
#include <vector>
#include <any>

template<typename T>
using Object = std::variant<std::vector<T>, std::map<std::string, T>, std::unordered_map<std::string, T>>;


#endif // REACTIVE_BASETYPE_H
