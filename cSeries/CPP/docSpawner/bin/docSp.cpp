// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: docSpawner
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/23 下午3:24
 * @Commend:
 *******************************************************/

#include "docSp.h"

namespace Global {
    std::vector<std::string> fieldTypes = {"Attributes:", "Methods:", ":param", ":return", "Example:", "example:", ":raises", ":type"};
}

namespace Tools {
    Json::Value jsonOpen(const std::string& path) {
        std::ifstream ifile;
        ifile.open(path);

        Json::CharReaderBuilder builder;
        builder["emitUTF8"] = true;

        Json::Value root;

        std::string errs;

        if (!Json::parseFromStream(builder, ifile, &root, &errs)) std::cerr << "parse error: " << errs << std::endl;

        return root;
    }

    std::string replace(std::string& str, const std::string& old, const std::string& new_) {
        size_t pos = 0;
        while ((pos = str.find(old)) != std::string::npos) {
            str.replace(pos, old.length(), new_);
            pos += new_.length();
        }
        return str;
    }
}  // namespace Tools

namespace Parser {
    std::string _desc(const std::string& comment) {
        // 将注释中的空格替换为(#s#)
        auto result = std::regex_replace(comment, std::regex{R"(?<=\S)\s(?=\S)"}, "(#s#)");

        // 去除注释中的空行
        result = Tools::replace(result, " ", "");

        // 寻找两次换行的位置
        result = result.substr(0, result.find("\n\n"));

        // 去除自定义符号
        result = Tools::replace(result, "(#s#)", "");

        assert(std::all_of(Global::fieldTypes.begin(), Global::fieldTypes.end(), [&result](const auto& field) { return result.find(field) != std::string::npos; }));

        return result;
    }

    namespace Class {}

    namespace Func {}
}  // namespace Parser
