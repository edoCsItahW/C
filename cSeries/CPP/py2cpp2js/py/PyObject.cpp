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
 * @Date: 2024/08/02 下午5:22
 * @Commend:
 *******************************************************/

#include "PyObject.h"

/**
 * [外部调用]python的Object类不允许传入参数,如非空应抛出异常.
 *
 * @param info 调用信息
 * @return ObjectAdapter
 */
ObjectAdapter::ObjectAdapter(const node::CallbackInfo& info) : ObjectWrap(info) {

	if (info.Length())
		node::TypeError::New(info.Env(), "object() takes no arguments").ThrowAsJavaScriptException();

	initPython();

	auto thisObject = info.This().As<node::Object>();

	MG__doc__ = node::String::New(info.Env(), getPyAttr("object", "__doc__").cast<std::string>());

	thisObject.Set("__doc__", MG__doc__);

}

node::Object ObjectAdapter::Init(node::Env env, node::Object exports) {
	node::Function func = DefineClass(
		env,
		"PyObject",
		{
			InstanceAccessor("__doc__", &ObjectAdapter::getDoc, nullptr)
		}
    );
	exports.Set(node::Symbol::New(env, "PyObject"), func);
	return exports;
}

node::Value ObjectAdapter::getDoc(const node::CallbackInfo& info) {
	return MG__doc__;
}
