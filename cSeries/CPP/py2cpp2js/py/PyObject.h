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
 * @Commend: 通过C++连接python以面向Node.js
 *******************************************************/


#ifndef BRIDGE_PYOBJECT_H
#define BRIDGE_PYOBJECT_H

#pragma once

#include "funcKit.h"

/** Object类是用来继承的,作为抽象基类,它的职责是为子类提供通用接口(通常是魔术方法或属性),而不应接受任何参数.
 *
 * @brief 实现python的Object类.
 */
class ObjectAdapter : public node::ObjectWrap<ObjectAdapter> {
	protected:

		// 魔术属性
		node::String MG__doc__;  // 文档字符串.

	public:
		explicit ObjectAdapter(const node::CallbackInfo &info);  // [外部调用]python的Object类不允许传入参数,如非空应抛出异常.
		static node::Object Init(node::Env env, node::Object exports);
		node::Value getDoc(const node::CallbackInfo &info);  // 获取文档字符串.
};


#endif // BRIDGE_PYOBJECT_H
