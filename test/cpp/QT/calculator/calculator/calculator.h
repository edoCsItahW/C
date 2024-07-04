// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: test
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/04 下午6:33
 * @Commend:
 *******************************************************/
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <regex>
#include <tuple>


using namespace std;


using Number = variant<int, float>;


class Operation {
public:
	Operation(Number left, Number right): left_(left), right_(right) {}

	[[nodiscard]] virtual Number result() const = 0;

	~Operation() = default;

protected:
	Number left_;
	Number right_;

};


class OperationAdd: public Operation {
public:
	OperationAdd(Number left, Number right): Operation(left, right) {}

	[[nodiscard]] Number result() const override {
		return visit([](auto&& left, auto&& right) -> Number {
						 return left + right;}, left_, right_);
	}
};


class OperationSub: public Operation {
public:
	OperationSub(Number left, Number right): Operation(left, right) {}

	[[nodiscard]] Number result() const override {
		return visit([](auto&& left, auto&& right) -> Number {
						 return left - right;}, left_, right_);
	}
};


class OperationMul: public Operation {
public:
	OperationMul(Number left, Number right):
		Operation(left, right) {}

	[[nodiscard]] Number result() const override {
		return visit([](auto&& left, auto&& right) -> Number {
						 return left * right;}, left_, right_);
	}
};


class OperationDiv: public Operation {
public:
	OperationDiv(Number left, Number right):
		Operation(left, right) {}

	[[nodiscard]] Number result() const override {
		return visit([](auto&& left, auto&& right) -> Number {
						 return left / right;}, left_, right_);
	}
};


class OperationFactory {
public:
	OperationFactory(string op): op_(std::move(op)) {}

	unique_ptr<Operation> create(Number left, Number right) {
		if (op_ == "+") return make_unique<OperationAdd>(left, right);
		else if (op_ == "-") return make_unique<OperationSub>(left, right);
		else if (op_ == "*") return make_unique<OperationMul>(left, right);
		else if (op_ == "/") return make_unique<OperationDiv>(left, right);
		else throw invalid_argument("Invalid operator");
	}

private:
	string op_;

};


ostream& operator<<(ostream& os, const Number& num) {
	visit([&os](auto&& arg) { os << arg; }, num);
	return os;
}


template <typename T>
T getVarFromNumber(T num) {
	if (holds_alternative<int>(num)) return get<int>(num);
	else if (holds_alternative<float>(num)) return get<float>(num);
	else throw invalid_argument("Invalid number type");
}
