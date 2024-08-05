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
 * @Date: 2024/08/04 上午3:11
 * @Commend:
 *******************************************************/

#ifndef BRIDGE_FUNCKIT_H
#define BRIDGE_FUNCKIT_H

#pragma once

#include <napi.h>
#include <pybind11/pybind11.h>
#include <map>
#include <iostream>
#include <functional>
#include <vector>

namespace py = pybind11;


namespace FuncKit {
	template<class T, class U = py::object>
	/**
	 * @tparam T 子类模板参数
	 * @tparam U 父类模板参数
	 * @brief 检测T是否是U的子类
	 */
	concept isChildOf = std::is_base_of<U, T>::value;

	template<typename F, typename T>
	/**
	 * @brief 转换python对象为cpp对象的函数模板
	 * @tparam F 转换函数类型,必须满足Py2CppFn concept.
	 * @tparam T 一个辅助检查类型,用于检查转换函数的返回类型是否与T一致.
	 */
	concept Py2CppFn = requires(F fn, py::object obj) { { fn(obj) } -> std::same_as<T>; };

	template<typename F, typename T>
	/**
	 * @brief 转换cpp对象为js对象的函数模板
	 * @tparam F 转换函数类型,必须满足Cpp2JsFn concept.
	 * @tparam T 一个辅助检查类型,用于检查转换函数作用于该类型后的返回类型是否与node::Value一致.
	 */
	concept Cpp2JsFn = requires(F fn, T cpp) { { fn(cpp) } -> std::same_as<Napi::Value>; };

	/** @brief python对象attr方法的返回类型,即python对象的属性类型 */
	using PyAttr = py::detail::accessor<py::detail::accessor_policies::str_attr>;

	/** 一个用于缓存python类的map(由于从模块导出同样返回PyAttr类型,所以不要误认为缓存的是类的属性)
	 *
	 * @property builtins 存贮导入的python内置模块,在构造函数中初始化.
	 * @brief 用于存储python类的map
	 * @note 该map仅提供get方法,set方法已隐含于get方法中.
	 * */
	class InsMap : public std::map<const char*, PyAttr> {
		private:
		py::module builtins;

		public:
		~InsMap() = default;
		InsMap() : std::map<const char*, PyAttr>() {
			builtins = py::module::import("builtins");
		}

		/** 在map中获取属性值,如果属性不存在,则导入该属性并返回
		 * @brief 获取属性值
		 * @param key 属性名
		 * @return 属性值
		 */
		PyAttr get(const char *key) {
			if (find(key) == end())
				this->insert(std::make_pair(key, builtins.attr(key)));
			return this->at(key);
		}
	};

}



#endif // BRIDGE_FUNCKIT_H
