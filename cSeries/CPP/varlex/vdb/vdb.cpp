// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File nodeName: VarLex
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/09/22 上午10:36
 * @Commend:
 *******************************************************/

#include "vdb.h"

namespace VDB {
    Try::Try(bool debug) : debug(debug) {}
    Try::Try() : debug(false) {}
    Try::~Try() = default;

    Try &Try::getInstance(bool debug) {
        static Try instance(debug);
        return instance;
    }

    template<typename F>
    auto Try::operator()(F fn, std::source_location loc) {
        return [fn, loc, this](auto&&... args) {
            try {
                if (debug) std::cout << std::format("File: {} line {} in {}", loc.file_name(), loc.line(), loc.function_name()) << std::endl;
                return fn(std::format<decltype(args)>(args)...);
            } catch (const std::exception &e) {
                std::cerr << std::format("File: {} line {} in {}", loc.file_name(), loc.line(), loc.function_name()) << std::endl;
            }
        };
    }

    Try& try_ = Try::getInstance(true);

    template<typename F>
    auto dbg(F fn, bool debug, std::source_location loc) {
        return [fn, debug, loc](auto&&... args) -> decltype(auto) {
            try {
                if (debug) std::cout << std::format("File: {} line {} in {}", loc.file_name(), loc.line(), loc.function_name()) << std::endl;
                return fn(std::format<decltype(args)>(args)...);
            } catch (const std::exception &e) {
                std::cerr << std::format("File: {} line {} in {}", loc.file_name(), loc.line(), loc.function_name()) << std::endl;
            }
        };
    }
}
