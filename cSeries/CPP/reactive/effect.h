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
 * @Date: 2024/07/31 下午1:53
 * @Commend:
 *******************************************************/

#ifndef REACTIVE_EFFECT_H
#define REACTIVE_EFFECT_H
#include <utility>
#include <vector>
#include <memory>
#include <functional>
#include "dep.h"
#include "computed.h"


template<typename T>
class ReactiveEffect {
private:
	bool active = true;
	std::vector<Dep<T>> deps{};
	ComputedRef<T> computed;

	int _trackId = 0;
	int _runnings = 0;
	int _depsLength = 0;

public:
	std::function<T> func;
	std::shared_ptr<std::function<void>> trigger;

	ReactiveEffect(std::shared_ptr<std::function<T>> func, std::shared_ptr<std::function<void>> trigger):
		func(func), trigger(std::move(trigger)) {}

	void run() {
		if (active)
			return func();
	}
};

#endif // REACTIVE_EFFECT_H
