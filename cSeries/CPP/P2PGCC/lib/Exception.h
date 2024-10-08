// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: P2PClient
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/22 上午3:22
 * @Commend:
 *******************************************************/

#ifndef P2PCLIENT_EXCEPTION_H
#define P2PCLIENT_EXCEPTION_H
#pragma once

#include <exception>
#include <iostream>
#include <utility>
#include <source_location>
#include <format>

class Exception : public std::exception {
	private:
		std::string eMsg;
        const std::source_location loc;
	public:
		explicit Exception(std::string msg, const std::source_location& loc = std::source_location::current()) : eMsg(std::move(msg)), loc(loc) {}

		[[nodiscard]] std::string getMsg() const { return std::format("{} line {} in <{}>", eMsg, loc.line(), loc.function_name()); }
};

#endif // P2PCLIENT_EXCEPTION_H
