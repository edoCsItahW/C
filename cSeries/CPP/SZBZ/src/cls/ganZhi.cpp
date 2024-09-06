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

#include "ganZhi.h"

GanZhi::GanZhi(GanZhi::U gan, GanZhi::U zhi)
    : _tianGan(std::move(gan))
    , _diZhi(std::move(zhi)) {}

template<>
int GanZhi::gan<int>() const {
    if (std::holds_alternative<int>(_tianGan))
        return std::get<int>(_tianGan);
    else if (std::holds_alternative<Global::TG_ENUM>(_tianGan))
        return static_cast<int>(std::get<Global::TG_ENUM>(_tianGan));
    else if (std::holds_alternative<TianGan>(_tianGan))
        return Global::TG_Map.index(std::get<TianGan>(_tianGan));
    throw std::bad_cast();
}

template<>
Global::TG_ENUM GanZhi::gan<Global::TG_ENUM>() const {
    if (std::holds_alternative<Global::TG_ENUM>(_tianGan))
        return std::get<Global::TG_ENUM>(_tianGan);
    else if (std::holds_alternative<int>(_tianGan))
        return static_cast<Global::TG_ENUM>(std::get<int>(_tianGan));
    else if (std::holds_alternative<TianGan>(_tianGan))
        return static_cast<Global::TG_ENUM>(Global::TG_Map.index(std::get<TianGan>(_tianGan)));
    throw std::bad_cast();
}

template<>
TianGan GanZhi::gan<TianGan>() const {
    if (std::holds_alternative<TianGan>(_tianGan))
        return std::get<TianGan>(_tianGan);
    else if (std::holds_alternative<int>(_tianGan))
        return Global::TG_Map[std::get<int>(_tianGan)];
    else if (std::holds_alternative<Global::TG_ENUM>(_tianGan))
        return Global::TG_Map[std::get<Global::TG_ENUM>(_tianGan)];
    throw std::bad_cast();
}

template<>
Global::DZ_ENUM GanZhi::zhi<Global::DZ_ENUM>() const {
    if (std::holds_alternative<Global::DZ_ENUM>(_diZhi))
        return std::get<Global::DZ_ENUM>(_diZhi);
    else if (std::holds_alternative<int>(_diZhi))
        return static_cast<Global::DZ_ENUM>(std::get<int>(_diZhi));
    else if (std::holds_alternative<DiZhi>(_diZhi))
        return static_cast<Global::DZ_ENUM>(Global::DZ_Map.index(std::get<DiZhi>(_diZhi)));
    throw std::bad_cast();
}

template<>
DiZhi GanZhi::zhi<DiZhi>() const {
    if (std::holds_alternative<DiZhi>(_diZhi))
        return std::get<DiZhi>(_diZhi);
    else if (std::holds_alternative<int>(_diZhi))
        return Global::DZ_Map[std::get<int>(_diZhi)];
    else if (std::holds_alternative<Global::DZ_ENUM>(_diZhi))
        return Global::DZ_Map[std::get<Global::DZ_ENUM>(_diZhi)];
    throw std::bad_cast();
}

template<>
int GanZhi::zhi<int>() const {
    if (std::holds_alternative<int>(_diZhi))
        return std::get<int>(_diZhi);
    else if (std::holds_alternative<Global::DZ_ENUM>(_diZhi))
        return static_cast<int>(std::get<Global::DZ_ENUM>(_diZhi));
    else if (std::holds_alternative<DiZhi>(_diZhi))
        return Global::DZ_Map.index(std::get<DiZhi>(_diZhi));
    throw std::bad_cast();
}

std::ostream &operator<<(std::ostream &os, const GanZhi &gz) {
    os << gz.gan<std::string>() << gz.zhi<std::string>();
    return os;
}
