// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: sdlDev
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/29 上午12:55
 * @Commend:
 *******************************************************/

#ifndef SDLDEV_GLOBAL_H
#define SDLDEV_GLOBAL_H
#pragma once

#include "cls/diZhi.h"
#include "cls/enumMap.h"
#include "cls/tianGan.h"
#include <any>
#include <codecvt>
#include <cstring>
#include <iostream>
#include <json/json.h>
#include <locale>
#include <ranges>
#include <sstream>
#include <string>
#include <variant>
#include <vector>
#include <windows.h>

class GanZhi;

namespace TG {
    extern TianGan Jia;
    extern TianGan Yi;
    extern TianGan Bing;
    extern TianGan Ding;
    extern TianGan Wu;
    extern TianGan Ji;
    extern TianGan Geng;
    extern TianGan Xin;
    extern TianGan Ren;
    extern TianGan Gui;
}  // namespace TG

namespace DZ {
    extern DiZhi Zi;
    extern DiZhi Chou;
    extern DiZhi Yin;
    extern DiZhi Mao;
    extern DiZhi Chen;
    extern DiZhi Si;
    extern DiZhi Wu;
    extern DiZhi Wei;
    extern DiZhi Shen;
    extern DiZhi You;
    extern DiZhi Xu;
    extern DiZhi Hai;
}

namespace Global {
    /** 十天干列表 */
    extern std::vector<TianGan> TG_VEC;
    /** 十天干枚举 */
    enum class TG_ENUM;
    /** 十天干映射 */
    extern Map<TianGan, TG_ENUM> TG_Map;
    /** 十二地支列表 */
    extern std::vector<DiZhi> DZ_VEC;
    /** 十二地支枚举 */
    enum class DZ_ENUM;
    /** 十二地支映射 */
    extern Map<DiZhi, DZ_ENUM> DZ_Map;
    /** 月令列表 */
    extern std::vector<std::string> YUE_LING;

}  // namespace Global

namespace Tools {
    namespace glb = Global;
    /** @brief 调用API获取数据
     *
     * @param year 年份
     * @param month 月份
     * @param day 日
     * @return std::string 返回的json字符串
     * */
    std::string _callApi(int year, int month, int day);
    /** @brief 解析json字符串
     *
     * @param jsonStr json字符串
     * @return Json::Value 返回的json对象
     * */
    Json::Value parseJson(std::string& jsonStr);
    /** @brief 获取干支
     *
     * @param year 年份
     * @param month 月份
     * @param day 日
     * @return std::vector<GanZhi> 返回的干支数组
     * */
    std::vector<GanZhi> getGanZhi(int year, int month, int day);
    bool _inRange(int x, int num1, int num2);
    /**
     * 甲己还加甲
     * 乙庚丙作初
     * 丙辛从戊起
     * 丁壬庚子居
     * 戊癸何方法，壬子是真途
     * */
    GanZhi getHour(int day, int hour);
}  // namespace Tools

#endif  // SDLDEV_GLOBAL_H
