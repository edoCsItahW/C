// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: MYSQLAPI
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/20 下午3:54
 * @Commend:
 *******************************************************/
//#include <boost/filesystem.hpp>
#include <pybind11/pybind11.h>
#include "fileSize.h"


//namespace py = pybind11;


//PYBIND11_MODULE(Path, m) {
//	m.doc() = "A module written in C++ for extensive python path operations";
//
//}

int main() {
	std::cout << getFileSize(R"(E:\ProgramFiles\cppPackage\boost_1_85_0\stage\lib)") << std::endl;
	return 0;
}
