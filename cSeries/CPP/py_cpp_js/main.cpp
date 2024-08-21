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
 * @Date: 2024/08/18 下午2:34
 * @Commend:
 *******************************************************/

#include "py/type/PyObject.h"

node::Object Init(node::Env env, node::Object exports) {
	ObjectAdapter::Init(env, exports);

	exports.Set("pyImport", node::Function::New(env, Api::import_, "pyImport"));
	return exports;
}

NODE_API_MODULE(builtins, Init)
