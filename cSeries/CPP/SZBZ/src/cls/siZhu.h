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
 * @Date: 2024/08/31 下午4:55
 * @Commend:
 *******************************************************/

#ifndef SZBZ_SIZHU_H
#define SZBZ_SIZHU_H
#pragma once

#include "ganZhi.h"

std::vector<GanZhi> getGanZhi(int year, int month, int day);

GanZhi getHour(int day, int hour);

class SiZhu {
    private:
        GanZhi year;
        GanZhi month;
        GanZhi day;
        GanZhi hour;

    public:

        SiZhu(const std::string& year, const std::string& month, const std::string& day, const std::string& hour = "甲子");
        SiZhu(GanZhi year, GanZhi month, GanZhi day, GanZhi hour);
        SiZhu(int year, int month, int day, int hour = 0);

        friend std::ostream& operator<<(std::ostream& os, const SiZhu& sz);
};

std::ostream &operator<<(std::ostream &os, const SiZhu &sz);

#endif  // SZBZ_SIZHU_H
