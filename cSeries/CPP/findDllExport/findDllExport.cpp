// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: COMBINE
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/25 上午11:08
 * @Commend:
 *******************************************************/
#include <array>
#include <iostream>
#include <regex>
#include <optional>

using namespace std;


string getExportInfo(const string &dllPath) {
	string cmd = "dumpbin /exports " + dllPath;

	FILE* pipe = _popen(cmd.c_str(), "r");

	if (!pipe) {
		cerr << "Failed to execute command" << endl;
		return "Failed to execute command";
	}

	array<char, 1024> buffer{};
	string result;

	while (!feof(pipe)) if (fgets(buffer.data(), buffer.size(), pipe) != nullptr) result += buffer.data();

	_pclose(pipe);

	return std::move(result);

}


vector<string> findall(const string& str, const regex& pattern) {
	vector<string> matches;
	sregex_iterator iter(str.begin(), str.end(), pattern);
	sregex_iterator end;

	while (iter != end) {
		smatch match = *iter;
		matches.push_back(match.str());
		iter++;
	}
	return matches;
}


void findSymbol(const string& dllPath, const string& symbol, const string& pattern) {
	vector<string> matches = findall(getExportInfo(dllPath), regex(pattern));

	for (const auto& info : matches)
		if (info.find(symbol) != string::npos)
			cout << "'" << symbol << "'" << " found in <" << info << "> of '" << dllPath << "'" << endl;
}


void findSymbol(const string& dllPath, const string& symbol) {
	findSymbol(dllPath, symbol, R"(_Z.*(?=\n))");
}


void findMultiSymbol(const string& dllPath, const vector<string>& symbols, const string& pattern) {
	vector<string> matches = findall(getExportInfo(dllPath), regex(pattern));

	for (const auto& symbol : symbols)
		for (const auto& info : matches)
			if (info.find(symbol) != string::npos)
				cout << "'" << symbol << "'" << " found in <" << info << "> of '" << dllPath << "'" << endl;

}


void findMultiSymbol(const string& dllPath, const vector<string>& symbols) {
	findMultiSymbol(dllPath, symbols, R"(_Z.*(?=\n))");
}


void findMMSymbol(const vector<string>& dllPaths, const vector<string>& symbols, const string& pattern) {
	for (const auto& dllPath : dllPaths)
		findMultiSymbol(dllPath, symbols, pattern);
}


void findMMSymbol(const vector<string>& dllPaths, const vector<string>& symbols) {
	findMMSymbol(dllPaths, symbols, R"(_Z.*(?=\n))");
}


int main() {
	string dllPath = R"(E:\ProgramFiles\cppPackage\boost_1_85_0\stage\lib\libboost_python311-mgw13-mt-x64-1_85.dll.a)";
	string dllPath2 = R"(E:\ProgramFiles\cppPackage\boost_1_85_0\stage\lib\libboost_python311-mgw13-mt-d-x64-1_85.dll.a)";

//	findSymbol(dllPath, "throw_error_already_set");
//	findMultiSymbol(dllPath, {"throw_error_already_set", "do_return_to_python"});
	findMMSymbol({dllPath, dllPath2}, {"throw_error_already_set", "do_return_to_python"});

	return 0;
}

