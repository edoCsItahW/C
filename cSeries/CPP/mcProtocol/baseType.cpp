// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: C
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/06/13 上午10:13
 * @Commend:
 *******************************************************/
#define IGNORE_WARNINGS = false
#include <iostream>
#include <utility>
#include <variant>
#include <vector>
#include <string>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <type_traits>


// -------------------- 数据类型定义 --------------------------


using bytes = std::vector<std::byte>;

using DataType = std::variant<int, bool, bytes, std::string>;


enum class Mode {
	error,
	warn
};


enum class orderMode {
	big,
	little
};


// -------------------- 静态方法定义 --------------------------


void warn(const std::string& msg) {

	std::cerr << "Warning: " << msg << std::endl;

}


int bytesToInt(const bytes& value, orderMode mode = orderMode::big) {

	if (value.size() < sizeof(int)) warn("Byte vector is too small to hold an int!");

	int result = 0;

	if (mode == orderMode::big) {
		for (size_t i = 0; i < sizeof(int); i++)
			result = (result << 8) | static_cast<unsigned char>(value[i]);
	}

	return result;

}


bytes intToBytes(int value, orderMode mode = orderMode::big) {

	bytes result(sizeof(int));

	if (mode == orderMode::big) {

		for (size_t i = 0; i < sizeof(int); i++) {
			result[i] = static_cast<std::byte>(value & 0xff);
			value >>= 8;
		}

	}

	return result;

}


// -------------------- 类定义 -------------------------------


class BaseType {

protected:
	DataType _data;

	BaseType(DataType data): _data(std::move(data)) {}

public:
	virtual ~BaseType() = default;

	bytes getBytes() {
		if (std::holds_alternative<int>(_data)) {

			int intValue = std::get<int>(_data);

			warn("Automatic conversion of int to byte type!");

			return bytes(reinterpret_cast<std::byte*>(&intValue), reinterpret_cast<std::byte*>(&intValue) + sizeof(int));

		}

		return std::get<bytes>(_data);

	}

	int getInt() {

		if (std::holds_alternative<bytes>(_data)) {

			bytes byteVec = std::get<bytes>(_data);

			warn("Automatic conversion of byte type to int!");

			return *reinterpret_cast<int*>(byteVec.data());

		}

		return std::get<int>(_data);

	}



};


class Boolean: public BaseType {

public:
	Boolean(DataType value): BaseType(std::move(value)) {}

};

