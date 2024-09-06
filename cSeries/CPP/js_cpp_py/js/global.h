// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: bridge
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/27 下午4:07
 * @Commend:
 *******************************************************/

#ifndef BRIDGE_GLOBAL_H
#define BRIDGE_GLOBAL_H
#pragma once

#include <v8.h>
#include <pybind11/pybind11.h>
#include <iostream>

namespace node = v8;
namespace py = pybind11;

namespace Global {
    extern node::Isolate* isolate;
    extern node::HandleScope scope;
}

node::Local<node::String> jsHello();

std::string cppHelloFromJS();

py::str pyHelloFromJS();

#endif  // BRIDGE_GLOBAL_H
