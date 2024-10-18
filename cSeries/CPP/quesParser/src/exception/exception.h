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
 * @brief 定义题目解析器异常类API头文件
 * @copyright CC BY-NC-SA
 * */

#ifndef QUESPARSER_EXCEPTION_H
#define QUESPARSER_EXCEPTION_H
#pragma once

#include <source_location>
#include <stdexcept>

class Exception : public std::runtime_error {
protected:
    const char* _type = "Error";

private:
    std::string _msg;
    std::source_location _loc;

public:
    explicit Exception(const std::string& msg, const std::source_location& loc = std::source_location::current());
    [[nodiscard]] const char* what() const noexcept override;
};

class ParseException : public Exception {
public:
    explicit ParseException(const std::string& msg, const std::source_location& loc = std::source_location::current());
};

#endif  // QUESPARSER_EXCEPTION_H
