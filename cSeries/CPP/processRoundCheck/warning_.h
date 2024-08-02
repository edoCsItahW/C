// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: ProcessRoundCheck
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/10 下午6:02
 * @Commend:
 *******************************************************/
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <format>


int WARNING_LEVEL = 3;


using WarnLevel = enum {
	DEBUG,
	INFO,
	WARNING,
	ERROR_,
	CRITICAL
};


template<typename... Args>
/** 用于输出等级超过全局变量WARNING_LEVEL的警告信息
 *
 * @tparam Args 可变参数模板
 * @param level 警告级别,来自WarnLevel枚举,大于等于WARNING_LEVEL时输出警告信息,有DEBUG,INFO,WARNING,ERROR_,CRITICAL五种级别
 * @param format 格式化字符串,支持{}占位符
 * @param args 格式化参数
 * @return void
 */
void warn(const WarnLevel level, const std::string_view& format, Args&&... args) {
	if (level >= WARNING_LEVEL) {
		std::string message = std::vformat(format, std::make_format_args(args...));

		std::cout << message << std::endl;
	}
}


template<typename... Args>
/** 弹出系统警告框,支持格式化字符串和{}占位符
 *
 * @tparam Args 可变参数模板
 * @param format 格式化字符串,支持{}占位符
 * @param args 格式化参数
 * @return void
 */
void alert(const std::string_view& format, Args&&... args) {
	std::string message = std::format(format, std::make_format_args(args...));

	MessageBox(nullptr, message.c_str(), "Warning", MB_OK | MB_ICONWARNING);
}
