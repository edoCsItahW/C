// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: P2PServer
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/22 下午11:12
 * @Commend:
 *******************************************************/
export module global;

#ifndef P2PSERVER_GLOBAL_H
#define P2PSERVER_GLOBAL_H
#pragma once

import <map>;
import <iostream>;
import <utility>;
import <exception>;


export namespace Error {
    /** @brief 抽象错误基类
     * @details 继承自std::exception，用于抛出错误信息
     * */
    class Exception : public std::exception {
        protected:
            std::string _msg;

        public:
            explicit Exception(std::string msg);
            [[nodiscard]] const char* what() const noexcept override;
    };

    class CMDError : public Exception {
        protected:
            std::string _msg;

        public:
            explicit CMDError(std::string msg);
    };
}

namespace Global {
    extern std::map<std::string, Error::Exception> errorLog;
    extern std::string token;
}

#endif  // P2PSERVER_GLOBAL_H
