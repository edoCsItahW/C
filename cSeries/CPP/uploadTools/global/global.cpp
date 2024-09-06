// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: P2PServer
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/22 下午11:12
 * @Commend:
 *******************************************************/

#include "global.h"


namespace Error {
    Exception::Exception(std::string msg) : _msg(std::move(msg)) {}
    const char* Exception::what() const noexcept { return _msg.c_str(); }
    CMDError::CMDError(std::string msg) : Exception(std::move(msg)), _msg(std::move(msg)) {}
}

namespace Global {
    std::map<std::string, Error::Exception> errorMap{};
    std::string token = "pypi-AgENdGVzdC5weXBpLm9yZwIkYzkwNzZjMTItOWU5OS00YWM4LWFiMWEtYWQwMzU1ZGZkYWVkAAIqWzMsIjRiNDBlZjEwLWRhMmQtNDVlMC1hYjM0LTY1MDI3YzBkYTJmMyJdAAAGILpCa7oU6b1m6k7hUMmp-dybDNN5R1bWdGghvxjjaQll";
}
