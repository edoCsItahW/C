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
 * @Date: 2024/07/10 下午6:25
 * @Commend:
 *******************************************************/
#include <format>
#include <iostream>
#include <sstream>
#include <utility>


std::string pythonStyleError(const std::string& message, const std::string& file, int line, const std::string& func) {
	std::ostringstream oss;

	oss << "Traceback (most recent call last):\n"
		<< "  File " << file << ", line " << line << ", in " << func << "\n"
		<< message << "\n";

	return oss.str();
}


class ExceptionMoreInfo: public std::runtime_error {
private:
	std::string file_;
	int line_;
	std::string func_;

public:
	ExceptionMoreInfo(std::string& message, std::string& file, int line, std::string& func):
		std::runtime_error(message), file_(std::move(file)), line_(line), func_(func) {}

	explicit ExceptionMoreInfo(std::string& message): std::runtime_error(message), file_("anonymous"), line_(-1), func_("unknown") {}

	[[nodiscard]] std::string getFile() const { return file_; }

	[[nodiscard]] int getLine() const { return line_; }

	[[nodiscard]] std::string getFunc() const { return func_; }

	void arrest() const {
		std::string what_ = std::string(what());

		std::cerr << pythonStyleError(
			what_,
			file_,
			line_,
			func_
			) << std::endl;
	}

};
