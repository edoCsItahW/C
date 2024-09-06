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

#include "siZhu.h"

std::vector<GanZhi> getGanZhi(int year, int month, int day) {
    namespace glb = Global;
    auto data     = Tools::_callApi(year, month, day);
    auto json     = Tools::parseJson(data);

    auto _year  = json["year"];
    auto _month = json["month"];
    auto _day   = json["day"];

    return {GanZhi(_year[0].asString(), _year[1].asString()), GanZhi(_month[0].asString(), _month[1].asString()), GanZhi(_day[0].asString(), _day[1].asString())};
}

GanZhi getHour(int day, int hour) {
    int _hour;
    for (int i = 1, j = 23;; i++) {
        if (Tools::_inRange(hour, j, i * 2 - 1)) {
            _hour = i - 1;
            break;
        }
        j = i * 2 - 1;
    }

    return {day % 5 * 2, _hour};
}

SiZhu::SiZhu(const std::string &year, const std::string &month, const std::string &day, const std::string &hour)
    : year(std::string(1, year[0]), std::string(1, year[1]))
    , month(std::string(1, month[0]), std::string(1, month[1]))
    , day(std::string(1, day[0]), std::string(1, day[1]))
    , hour(std::string(1, hour[0]), std::string(1, hour[1])) {}

SiZhu::SiZhu(GanZhi year, GanZhi month, GanZhi day, GanZhi hour)
    : year(std::move(year))
    , month(std::move(month))
    , day(std::move(day))
    , hour(std::move(hour)) {}

SiZhu::SiZhu(int year, int month, int day, int hour) {
    auto ganZhi = getGanZhi(year, month, day);
    this->year  = ganZhi[0];
    this->month = ganZhi[1];
    this->day   = ganZhi[2];
    this->hour  = getHour(day, hour);
}

std::ostream &operator<<(std::ostream &os, const SiZhu &sz) {
    os << sz.year << "年 " << sz.month << "月 " << sz.day << "日 " << sz.hour << "时";
    return os;
}
