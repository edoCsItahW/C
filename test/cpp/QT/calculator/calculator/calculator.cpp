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
 * @Date: 2024/06/30 下午10:02
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
	Operation(Number left, Number right): left_(left), right_(right) {
		// 对于基本数据类型,没必要(也不能)使用std::move来改变语义,std::move只是为了避免拷贝构造函数的调用,但对于基本数据类型,拷贝构造函数的调用是没有意义的.
	}

	[[nodiscard]] virtual Number result() const = 0;


	~Operation() = default;
protected:
	Number left_;
	Number right_;

};


ostream& operator<<(ostream& os, const Number& num) {
	visit([&os](auto&& arg) { os << arg; }, num);
	return os;
}


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
		cout << "left: " << left_ << ", right: " << right_ << endl;
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


Number judgeType(const string& str) {
	if (str.find('.') != string::npos) {
		cout << "float: " << str << endl;
		return stof(str);
	}
	else return stoi(str);
}


tuple<Number, string, Number> parserString(const string& input) {
	regex pattern("^(.+)(?!=\\s)([*+/-])(?!=\\s)(.+)$");

	smatch result;

	if (regex_search(input, result, pattern)) {
		return {judgeType(result[1]), result[2], judgeType(result[3])};
	}

	return {Number {}, "", Number {}};
}


template <typename T>
T getVarFromNumber(T num) {
	if (holds_alternative<int>(num)) return get<int>(num);
	else if (holds_alternative<float>(num)) return get<float>(num);
	else throw invalid_argument("Invalid number type");
}


int main() {
	string input;

	cout << "Enter expression: " << endl;

	getline(cin, input);

	Number left, right;
	string op;

	tie(left, op, right) = parserString(input);

	cout << "left: " << left << ", op: " << op << ", right: " << right << endl;

	auto leftVar = getVarFromNumber(left);
	auto rightVar = getVarFromNumber(right);

	OperationFactory factory(op);
	unique_ptr<Operation> operation = factory.create(left, right);
	cout << "result: " << operation->result() << endl;

//	if (readNumber(cin, left) && cin >> op && readNumber(cin, right)) {
//		OperationFactory factory(op);
//		unique_ptr<Operation> operation = factory.create(left, right);
//		cout << operation->result() << endl;
//	}
//	else {
//		cerr << "Invalid input" << endl;
//	}

}
