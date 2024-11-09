// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file mathUtils.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/11/07 下午5:01
 * @brief
 * */
#include "mathUtils.h"

int gcd(int a, int b) {
    return b == 0? a : gcd(b, a % b);
}
