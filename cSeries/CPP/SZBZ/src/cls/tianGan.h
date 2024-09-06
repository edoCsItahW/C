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

#ifndef SZBZ_TIANGAN_H
#define SZBZ_TIANGAN_H

#include <string>

enum class YinYang { YIN, YANG };

class TianGan {
    public:
        std::string name;
        YinYang yinYang;

        TianGan(std::string  name, YinYang yinYang);

        bool operator==(const TianGan& other) const;
};

#endif  // SZBZ_TIANGAN_H
