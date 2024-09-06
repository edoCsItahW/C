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
 * @Date: 2024/08/23 下午11:59
 * @Commend:
 *******************************************************/

#ifndef DOCSPAWNER_EXCEPTION_H
#define DOCSPAWNER_EXCEPTION_H
#pragma once

#include <stdexcept>
#include <functional>
#include <source_location>
#include <stacktrace>
#include <sstream>
#include <iostream>

class Exception : public std::runtime_error {

};

template<typename R, typename... Args>
auto wrap(R(*f)(Args...), std::source_location loc = std::source_location::current()) {
    return [f, loc](Args... args) -> R {
        try {
            return f(args...);
        }
        catch (const std::exception& e) {
            std::ostringstream oss;
            oss << "Traceback (most recent call last):\n"
                   "\tFile " << loc.file_name() << ", line " << loc.line() << ", in " << loc.function_name() << "\n"
                << e.what() << "\n";

            std::cerr << oss.str() << std::endl;
        }
    };
}

#endif  // DOCSPAWNER_EXCEPTION_H
