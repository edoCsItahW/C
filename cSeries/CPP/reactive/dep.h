// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: REACTIVE
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/31 下午1:49
 * @Commend:
 *******************************************************/

#ifndef REACTIVE_DEP_H
#define REACTIVE_DEP_H
#include <map>
#include "computed.h"


template <typename T>
class ReactiveEffect;


template <typename T>
class Dep : public std::map<std::shared_ptr<ReactiveEffect<T>>, int>{
private:
	std::function<void()> _cleanup;
	std::shared_ptr<ComputedRef<T>> _computedRef;

public:
	Dep() = default;

	explicit Dep(std::function<void()> cleanup, std::shared_ptr<ComputedRef<T>> computedRef): std::map<std::shared_ptr<ReactiveEffect<T>>, int>() {
		_cleanup = std::move(cleanup);
		_computedRef = computedRef;
	}

	[[nodiscard]] std::shared_ptr<std::function<void()>> cleanup() const {
		return std::make_shared<std::function<void()>>(_cleanup);
	}

	std::shared_ptr<ComputedRef<T>> computedRef() const {
		return _computedRef;
	}

};

#endif // REACTIVE_DEP_H
