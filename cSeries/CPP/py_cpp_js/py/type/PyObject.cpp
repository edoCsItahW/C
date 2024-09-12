// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: py_cpp_js
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/18 下午2:45
 * @Commend:
 *******************************************************/

#include "PyObject.h"

// const char* ObjectAdapter::name = "PyObject";

// bool ObjectAdapter::setAble = false;

ObjectAdapter::ObjectAdapter(const node::CallbackInfo &info)
    : ObjectWrap(info) {
    //	if (info.Length()) Error::ArgumentError(info.Env(), "ValueError: ObjectAdapter constructor takes no arguments!");

    module = Glb::builtins.attr("object");

    instance = module(*Py::Tools::getArgs(info));
}

node::Value ObjectAdapter::get(const node::CallbackInfo &info) {
    if (info.Length() != 1) node::Error::New(info.Env(), "ValueError: ObjectAdapter.get() takes exactly one argument!");

    auto key = info[0].ToString().Utf8Value();

    if (attrs.count(key)) return attrs[key];

    if (!hasattr(instance, key.c_str())) node::Error::New(info.Env(), "AttributeError: object has no attribute '" + key + "'!");

    return Py::Converter::pyToJs(info.Env(), instance.attr(Js::Converter::jsToPy(info[0])));
}

void ObjectAdapter::set(const node::CallbackInfo &info) {
    //	if (!setAble) node::Error::New(info.Env(), "AttributeError: can't set attribute of built-in/extension type 'object'!");

    if (info.Length() != 2) Err::ArgumentError(info.Env(), "ValueError: ObjectAdapter.set() takes exactly two arguments!");

    auto key = info[0].ToString().Utf8Value();

    if (!hasattr(instance, key.c_str())) attrs.insert({key, info[1]});
}

node::Object ObjectAdapter::Init(node::Env env, node::Object exports) {
    auto func = DefineClass(env, "PyObject", {InstanceMethod("get", &ObjectAdapter::get)});

    exports.Set("PyObject", func);
    return exports;
}
