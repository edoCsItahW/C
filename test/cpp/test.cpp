// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

//
// Created by Lenovo on 24-5-6.
//
#include <iostream>
#include <iomanip>
#include <vector>

struct PersonInfo {
	std::string name;
	std::vector<std::string> phones;
};

int main() {
	std::string line, word;

	std::vector<PersonInfo> people;

	while (std::getline(std::cin, line)) {

		PersonInfo info;

		std::istringstream record(line);

		std::cout << "name: " << std::endl;

		record >> info.name;

		while (record >> word)

			std::cout << "phone: " << std::endl;

			info.phones.push_back(word);

		people.push_back(info);

	}



	return 0;
}
