// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: docSpawner
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/23 下午3:24
 * @Commend: 解析python说明注释
 *******************************************************/

#ifndef DOCSPAWNER_DOCSP_H
#define DOCSPAWNER_DOCSP_H
#pragma once

#include "include/json/json.h"
#include <fstream>
#include <iostream>
#include <map>
#include <pybind11/pybind11.h>
#include <regex>
#include <vector>
#include <ranges>

namespace py = pybind11;

namespace Global {
    extern py::module ast;
    extern std::string result;
    extern std::vector<std::string> fieldTypes;
}  // namespace Global

namespace Tools {
    Json::Value jsonOpen(const std::string& path);
    std::string replace(const std::string& str, const std::string& old, const std::string& new_);
}

namespace Parser {
    std::string _desc(const std::string& comment);
    std::string _example(const std::string& comment);

    namespace Class {
        std::string _method(const std::string& comment);
        std::string _attrs(const std::string& comment);
    }  // namespace Class

    namespace Func {
        /** @brief 解析函数类型的注释
         * @param comment 完整注释内容
         * @return 解析后的函数类型注释
         * */
        std::string _param(const std::string& comment);
    }
}  // namespace Parser

#endif  // DOCSPAWNER_DOCSP_H
