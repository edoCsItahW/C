// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: FILESIZE
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/31 上午11:19
 * @Commend: 仿写Vue3的响应式系统
 *******************************************************/
#include <any>
#include <iostream>
#include <map>
#include <unordered_map>
#include <memory>
#include <functional>
#include <utility>
#include "baseType.h"
#include "dep.h"
#include "effect.h"
//struct AnyHash {
//	template <typename T>
//	std::size_t operator()(const std::any& a) const {
//		return std::hash<T>{}(std::any_cast<T>(a));
//	}
//};

//struct AnyEq {
//	template <typename T>
//	bool operator()(const std::any& lhs, const std::any& rhs) const {
//		return std::any_cast<T>(lhs) == std::any_cast<T>(rhs);
//	}
//};

template <typename T, typename U, typename V>
std::map<std::shared_ptr<Object<T>>, std::map<U, Dep<V>>> TARGET_MAP = {};
bool SHOULD_TRACK = true;
ReactiveEffect* ACTIVE_EFFECT = nullptr;

template <typename T>
class Ref;

template <typename T>
void trackEffect(ReactiveEffect* effect, Dep<T>& dep) {
	if (dep[effect] != effect.trackId())
}

template <typename T>
void track(const std::shared_ptr<Object<T>>& target, const std::string& key) {
	if (SHOULD_TRACK && ACTIVE_EFFECT) {
		std::map<const std::string, Dep<T>>& depMap = TARGET_MAP<T, const std::string, T>[target];

		if (!depMap.empty())
			TARGET_MAP<T, const std::string, T>[target] = (depMap = std::map<const std::string, Dep<T>>());

		auto& dep = depMap[key];

		if (!std::get<bool>(dep))
			depMap[key] = (dep = Dep<T>([depMap, key]() { depMap.erase(key); }));

		trackEffect<T>(ACTIVE_EFFECT, dep);

	}
}


template <typename T>
void trackRefValue(Ref<T>& ref) {

}


template <typename T>
class Ref {
private:
	T _value;
	T _raw;

public:
	explicit Ref(T value) : _value(value), _raw(value) {}

	[[nodiscard]] T value() const {
		return _value;
	}

};


int main() {
	Ref<int> ref(10);
	trackRefValue(ref);
	return 0;
}
