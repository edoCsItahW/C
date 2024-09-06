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
 * @Date: 2024/08/29 ÉÏÎç12:55
 * @Commend:
 *******************************************************/

#include "global.h"
#include <utility>

namespace TG {
    TianGan Jia = TianGan("¼×", YinYang::YANG);
    TianGan Yi = TianGan("ÒÒ", YinYang::YIN);
    TianGan Bing = TianGan("±û", YinYang::YANG);
    TianGan Ding = TianGan("¶¡", YinYang::YIN);
    TianGan Wu = TianGan("Îì", YinYang::YANG);
    TianGan Ji = TianGan("¼º", YinYang::YIN);
    TianGan Geng = TianGan("¸ý", YinYang::YANG);
    TianGan Xin = TianGan("ÐÁ", YinYang::YIN);
    TianGan Ren = TianGan("ÈÉ", YinYang::YANG);
    TianGan Gui = TianGan("¹ï", YinYang::YIN);
}

namespace DZ {
    DiZhi Zi = DiZhi("×Ó");
    DiZhi Chou = DiZhi("³ó");
    DiZhi Yin = DiZhi("Òú");
    DiZhi Mao = DiZhi("Ã®");
    DiZhi Chen = DiZhi("³½");
    DiZhi Si = DiZhi("ËÈ");
    DiZhi Wu = DiZhi("Îç");
    DiZhi Wei = DiZhi("Î´");
    DiZhi Shen = DiZhi("Éê");
    DiZhi You = DiZhi("ÓÏ");
    DiZhi Xu = DiZhi("Ðç");
    DiZhi Hai = DiZhi("º¥");
}

namespace Global {
    std::vector<TianGan> TG_VEC = {TG::Jia, TG::Yi, TG::Bing, TG::Ding, TG::Wu, TG::Ji, TG::Geng, TG::Xin, TG::Ren, TG::Gui};
    enum class TG_ENUM { Jia, Yi, Bing, Ding, Wu, Ji, Geng, Xin, Ren, Gui };
    Map<TianGan, TG_ENUM> TG_MAP(TG_VEC);
    std::vector<DiZhi> DZ_VEC = {DZ::Zi, DZ::Chou, DZ::Yin, DZ::Mao, DZ::Chen, DZ::Si, DZ::Wu, DZ::Wei, DZ::Shen, DZ::You, DZ::Xu, DZ::Hai};
    enum class DZ_ENUM { Zi, Chou, Yin, Mao, Chen, Si, Wu, Wei, Shen, You, Xu, Hai };
    Map<DiZhi, DZ_ENUM> DZ_Map(DZ_VEC);
    std::vector<std::string> YUE_LING = {"Á¢´º", "¾ªÕÝ", "ÇåÃ÷", "Á¢ÏÄ", "Ã¢ÖÖ", "Ð¡Êî", "Á¢Çï", "°×Â¶", "º®Â¶", "Á¢¶¬", "´óÑ©", "Ð¡º®"};
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
