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
 * @Date: 2024/08/02 下午7:53
 * @Commend:
 *******************************************************/

#ifndef BRIDGE_GLOBALVAR_H
#define BRIDGE_GLOBALVAR_H

#pragma once

#include <functional>
#include <map>
#include <optional>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>


namespace py = pybind11;

extern bool PYINITFLAG;

bool initPython() {
	if (!PYINITFLAG) {
		py::initialize_interpreter();
		PYINITFLAG = true;
	}
	return PYINITFLAG;
}

template<class T, class U = py::object>
concept isChildOf = std::is_base_of<U, T>::value;

class InsMap : public std::map<std::string, std::shared_ptr<py::object>> {
	private:

	public:
		InsMap() = default;
		~InsMap() = default;

		template<isChildOf<py::object> T = py::object>
		std::shared_ptr<T> get(const std::string& key) {
			if (find(key) == end())
				this->insert(std::make_pair(key, std::make_shared<T>()));
			return std::static_pointer_cast<T>(at(key));
		}

		template<isChildOf<py::object> T = py::object>
		void set(const std::string& key, const std::shared_ptr<T>& value) {
			this->insert(std::make_pair(key, value));
		}
};


extern InsMap* INS_CACHE;

#endif // BRIDGE_GLOBALVAR_H
