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

#include "global.h"

namespace Global {
    node::Isolate* isolate = node::Isolate::New(node::Isolate::CreateParams());
    node::HandleScope scope(isolate);
}

node::Local<node::String> jsHello() {
    node::Local<node::Context> context = node::Context::New(Global::isolate);
    return node::String::NewFromUtf8(Global::isolate, "Hello, world from javascript!").ToLocalChecked();
}

std::string cppHelloFromJS() {
    auto text = jsHello();
    return *node::String::Utf8Value(Global::isolate, text);
}

py::str pyHelloFromJS() {
    return py::cast(cppHelloFromJS());
}