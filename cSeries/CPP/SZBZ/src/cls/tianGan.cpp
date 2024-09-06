// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: szbz
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/31 下午7:53
 * @Commend:
 *******************************************************/

#include "tianGan.h"

#include <utility>

TianGan::TianGan(std::string name, YinYang yinYang)
    : name(std::move(name))
    , yinYang(yinYang) {}

bool TianGan::operator==(const TianGan& other) const {
    return name == other.name;
}
