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
 * @Date: 2024/08/20 下午5:37
 * @Commend:
 *******************************************************/

#ifndef PY_CPP_JS_PYINT_H
#define PY_CPP_JS_PYINT_H

//#include "PyObject.h"

class IntAdapter : public ObjectAdapter {
	protected:
		py::object module;
		py::object instance;
		std::map<std::string, node::Value> attrs{};
		static const char* name;
		static bool setAble;
	public:
		explicit IntAdapter(const node::CallbackInfo& info);
		node::Object Init(node::Env env, node::Object exports);
};


#endif // PY_CPP_JS_PYINT_H
