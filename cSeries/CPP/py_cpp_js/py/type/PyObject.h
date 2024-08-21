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
 * @Date: 2024/08/18 下午2:35
 * @Commend:
 *******************************************************/

#ifndef PY_CPP_JS_PYOBJECT_H
#define PY_CPP_JS_PYOBJECT_H
#pragma once

#include "../global.h"

class ObjectAdapter : public node::ObjectWrap<ObjectAdapter> {
	protected:
		py::object module;
		py::object instance;
		std::map<std::string, node::Value> attrs{};
//		static const char* name;
//		static bool setAble;
	public:
		/* python的Object类不允许传入参数,如非空应抛出异常. */
		explicit ObjectAdapter(const node::CallbackInfo& info);
		node::Value get(const node::CallbackInfo& info);
		void set(const node::CallbackInfo& info);
		static node::Object Init(node::Env env, node::Object exports);
};

#endif // PY_CPP_JS_PYOBJECT_H
