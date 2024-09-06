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

#include "global.h"
#include <utility>

namespace TG {
    TianGan Jia = TianGan("��", YinYang::YANG);
    TianGan Yi = TianGan("��", YinYang::YIN);
    TianGan Bing = TianGan("��", YinYang::YANG);
    TianGan Ding = TianGan("��", YinYang::YIN);
    TianGan Wu = TianGan("��", YinYang::YANG);
    TianGan Ji = TianGan("��", YinYang::YIN);
    TianGan Geng = TianGan("��", YinYang::YANG);
    TianGan Xin = TianGan("��", YinYang::YIN);
    TianGan Ren = TianGan("��", YinYang::YANG);
    TianGan Gui = TianGan("��", YinYang::YIN);
}

namespace DZ {
    DiZhi Zi = DiZhi("��");
    DiZhi Chou = DiZhi("��");
    DiZhi Yin = DiZhi("��");
    DiZhi Mao = DiZhi("î");
    DiZhi Chen = DiZhi("��");
    DiZhi Si = DiZhi("��");
    DiZhi Wu = DiZhi("��");
    DiZhi Wei = DiZhi("δ");
    DiZhi Shen = DiZhi("��");
    DiZhi You = DiZhi("��");
    DiZhi Xu = DiZhi("��");
    DiZhi Hai = DiZhi("��");
}

namespace Global {
    std::vector<TianGan> TG_VEC = {TG::Jia, TG::Yi, TG::Bing, TG::Ding, TG::Wu, TG::Ji, TG::Geng, TG::Xin, TG::Ren, TG::Gui};
    enum class TG_ENUM { Jia, Yi, Bing, Ding, Wu, Ji, Geng, Xin, Ren, Gui };
    Map<TianGan, TG_ENUM> TG_MAP(TG_VEC);
    std::vector<DiZhi> DZ_VEC = {DZ::Zi, DZ::Chou, DZ::Yin, DZ::Mao, DZ::Chen, DZ::Si, DZ::Wu, DZ::Wei, DZ::Shen, DZ::You, DZ::Xu, DZ::Hai};
    enum class DZ_ENUM { Zi, Chou, Yin, Mao, Chen, Si, Wu, Wei, Shen, You, Xu, Hai };
    Map<DiZhi, DZ_ENUM> DZ_Map(DZ_VEC);
    std::vector<std::string> YUE_LING = {"����", "����", "����", "����", "â��", "С��", "����", "��¶", "��¶", "����", "��ѩ", "С��"};
}  // namespace Global

namespace Tools {
    namespace glb = Global;

    std::string _callApi(int year, int month, int day) {
        FILE *pipe = _popen(("CalAPI.exe " + std::to_string(year) + " " + std::to_string(month) + " " + std::to_string(day)).c_str(), "r");

        if (!pipe) throw std::runtime_error(std::string(__FUNCTION__) + ": _popen failed");

        std::ostringstream oss;

        char buffer[256];
        while (!feof(pipe))
            if (fgets(buffer, sizeof(buffer), pipe) != nullptr) oss << buffer;

        _pclose(pipe);

        return oss.str();
    }

    Json::Value parseJson(std::string& jsonStr) {
        Json::Value root;
        Json::Reader reader;

        while (jsonStr.contains("'")) jsonStr = jsonStr.replace(jsonStr.find('\''), 1, "\"");

        bool flag = reader.parse(jsonStr, root);
        if (!flag) throw std::runtime_error(std::string(__FUNCTION__) + ": parse json failed");

        return root;
    }

    bool _inRange(int x, int num1, int num2) {
        return (num1 < num2)
            ? (num1 <= x && x < num2)
            : ((0 <= x && x < num2) || (num1 <= x && x <= 24));
    }
}  // namespace Tools
