// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/16 下午7:10
 * @brief 定义题目解析器异常类API实现
 * @copyright CC BY-NC-SA
 * */

#include "exception.h"
#include <sstream>

Exception::Exception(const std::string &msg, const std::source_location &loc)
    : std::runtime_error(msg)
    , _msg(msg)
    , _loc(loc) {}

const char *Exception::what() const noexcept {
    std::ostringstream oss;
    oss << "File \"" << _loc.file_name() << ", line " << _loc.line() << ", in <" << _loc.function_name() << ">\n"
        << "\t" << _type << ": " << _msg;
    return oss.str().c_str();
}

ParseException::ParseException(const std::string &msg, const std::source_location &loc)
    : Exception(msg, loc) {
    _type = "ParseError";
}
