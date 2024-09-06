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
 * @Date: 2024/08/31 下午4:52
 * @Commend:
 *******************************************************/

#ifndef SZBZ_GANZHI_H
#define SZBZ_GANZHI_H
#pragma once

#include "../global.h"

class GanZhi {
        using U = std::variant<int, TianGan, DiZhi, Global::TG_ENUM, Global::DZ_ENUM>;
    private:
        U _tianGan;
        U _diZhi;

    public:
        GanZhi(U gan, U zhi);
        GanZhi() = default;

        template<typename T>
        T gan() const {
            throw std::bad_cast();
        }
        template<typename T>
        T zhi() const {
            throw std::bad_cast();
        }
};

template<>
[[nodiscard]] inline int GanZhi::gan<int>() const;
template<>
[[nodiscard]] inline Global::TG_ENUM GanZhi::gan<Global::TG_ENUM>() const;
template<>
[[nodiscard]] inline TianGan GanZhi::gan<TianGan>() const;
template<>
[[nodiscard]] inline Global::DZ_ENUM GanZhi::zhi<Global::DZ_ENUM>() const;
template<>
[[nodiscard]] inline DiZhi GanZhi::zhi<DiZhi>() const;
template<>
[[nodiscard]] inline int GanZhi::zhi<int>() const;

std::ostream &operator<<(std::ostream &os, const GanZhi &gz);

#endif  // SZBZ_GANZHI_H
