// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: bridging
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/09/18 下午12:43
 * @Commend:
 *******************************************************/

#include "PyType.h"

TypeAdapter::TypeAdapter(const node::CallbackInfo &info) : ObjectAdapter(info), module(Glb::builtins.attr("type")), instance(module(*Py::Tools::getArgs(info))) {}

node::Value TypeAdapter::get(const node::CallbackInfo &info) {

}