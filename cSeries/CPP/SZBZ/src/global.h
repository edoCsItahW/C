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
 * @Date: 2024/08/29 ����12:55
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
    /** ʮ����б� */
    extern std::vector<TianGan> TG_VEC;
    /** ʮ���ö�� */
    enum class TG_ENUM;
    /** ʮ���ӳ�� */
    extern Map<TianGan, TG_ENUM> TG_Map;
    /** ʮ����֧�б� */
    extern std::vector<DiZhi> DZ_VEC;
    /** ʮ����֧ö�� */
    enum class DZ_ENUM;
    /** ʮ����֧ӳ�� */
    extern Map<DiZhi, DZ_ENUM> DZ_Map;
    /** �����б� */
    extern std::vector<std::string> YUE_LING;

}  // namespace Global

namespace Tools {
    namespace glb = Global;
    /** @brief ����API��ȡ����
     *
     * @param year ���
     * @param month �·�
     * @param day ��
     * @return std::string ���ص�json�ַ���
     * */
    std::string _callApi(int year, int month, int day);
    /** @brief ����json�ַ���
     *
     * @param jsonStr json�ַ���
     * @return Json::Value ���ص�json����
     * */
    Json::Value parseJson(std::string& jsonStr);
    /** @brief ��ȡ��֧
     *
     * @param year ���
     * @param month �·�
     * @param day ��
     * @return std::vector<GanZhi> ���صĸ�֧����
     * */
    std::vector<GanZhi> getGanZhi(int year, int month, int day);
    bool _inRange(int x, int num1, int num2);
    /**
     * �׼����Ӽ�
     * �Ҹ�������
     * ����������
     * ���ɸ��Ӿ�
     * ���η�������������;
     * */
    GanZhi getHour(int day, int hour);
}  // namespace Tools

#endif  // SDLDEV_GLOBAL_H
