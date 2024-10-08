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

#ifndef BRIDGING_PYTYPE_H
#define BRIDGING_PYTYPE_H
#pragma once

#include "PyObject.h"

class TypeAdapter : public ObjectAdapter {
    protected:
        py::object module;
        py::object instance;

    public:
        explicit TypeAdapter(const node::CallbackInfo& info);
        node::Value get(const node::CallbackInfo& info);
};

#endif  // BRIDGING_PYTYPE_H
