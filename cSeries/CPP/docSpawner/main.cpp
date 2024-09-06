// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: P2PServer
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/23 下午3:19
 * @Commend:
 *******************************************************/

#include "bin/docSp.h"
#include "bin/exception.h"


int main() {
    auto data = Tools::jsonOpen("E:/codeSpace/codeSet/C/cSeries/CPP/docSpawner/bin/common.json");

    for (auto& item : data)
        std::cout << wrap(Parser::_desc)(item.asString()) << std::endl;
}
