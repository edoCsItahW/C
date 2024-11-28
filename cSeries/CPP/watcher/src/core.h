// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file core.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/11/22 上午10:24
 * @brief
 * */
#ifndef CBPD_CORE_H
#define CBPD_CORE_H
#pragma once

#include <array>
#include <iostream>
#include <string>
#include <tchar.h>
#include <windows.h>
#include <psapi.h>
#include <vector>

enum Warning {
    UserWarning,
    BytesWarning,
    FutureWarning,
    DeprecationWarning,
    PendingDeprecationWarning,
    SyntaxWarning,
    EncodingWarning,
    ImportWarning,
    ResourceWarning,
    RuntimeWarning,
    UnicodeWarning,
};

template<auto Value>
constexpr auto enumToStr();

template<typename T, std::size_t N = 0>
constexpr auto enumMax();

template<typename T>
    requires std::is_enum_v<T>
constexpr auto enumToStr(T value);

class FileEventHandleABC {
protected:
    std::wstring _path;

public:
    void setPath(std::wstring path);
    virtual void added()      = 0;
    virtual void removed()    = 0;
    virtual void modified()   = 0;
    virtual void renamedOld() = 0;
    virtual void renamedNew() = 0;
};

class FileEventHandler : public FileEventHandleABC {
public:
    void added() override;
    void removed() override;
    void modified() override;
    void renamedOld() override;
    void renamedNew() override;
};

struct watchKwargs {
    FileEventHandleABC* handler = nullptr;
    std::vector<std::wstring> filters = {};
};

void warn(const std::string& msg, Warning cotegory = UserWarning);

#define watch(path, ...) watch(path, watchKwargs{__VA_ARGS__})

[[noreturn]] void (watch)(const std::wstring& path, watchKwargs kwargs = {});

extern SERVICE_STATUS_HANDLE g_ServiceStatusHandle;
extern SERVICE_STATUS g_ServiceStatus;

void getRecentFileChangeLog();

void reportServiceStatus(DWORD state, DWORD exitCode, DWORD waitHint = 0);

void WINAPI serviceMain(DWORD argc, LPTSTR* argv);

void WINAPI serviceCtrlHandler(DWORD ctrl);

//int _tmain(int argc, TCHAR* argv[]);

#include "core.hpp"

#endif  // CBPD_CORE_H
