// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file core.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/11/22 上午10:24
 * @brief
 * */
#include "core.h"
#include <fcntl.h>
#include <ranges>

void warn(const std::string& msg, Warning cotegory) { std::cerr << enumToStr(cotegory) << ": " << msg << std::endl; }

void FileEventHandleABC::setPath(std::wstring path) { _path = std::move(path); }

void FileEventHandler::added() { std::wcout << L"[" << L"ADDED" << L"] '" << _path << L"'" << std::endl; }

void FileEventHandler::removed() { std::wcout << L"[" << L"REMOVED" << L"] '" << _path << L"'" << std::endl; }

void FileEventHandler::modified() { std::wcout << L"[" << L"MODIFIED" << L"] '" << _path << L"'" << std::endl; }

void FileEventHandler::renamedOld() { std::wcout << L"[" << L"RENAMED_OLD" << L"] '" << _path << L"'" << std::endl; }

void FileEventHandler::renamedNew() { std::wcout << L"[" << L"RENAMED_NEW" << L"] '" << _path << L"'" << std::endl; }

[[noreturn]] void (watch)(const std::wstring& path, watchKwargs kwargs) {
    _setmode(_fileno(stdout), _O_U16TEXT);

    HANDLE hDir = CreateFileW(path.c_str(), FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);

    if (hDir == INVALID_HANDLE_VALUE) warn("CreateFile failed!", ResourceWarning);

    BYTE buffer[1024];
    DWORD bytesReturned;

    while (true) {
        if (ReadDirectoryChangesW(hDir, &buffer, sizeof(buffer), TRUE, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE, &bytesReturned, nullptr, nullptr)) {
            auto* fni = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(&buffer);

            if (std::ranges::find(kwargs.filters, fni->FileName) != kwargs.filters.end())
                continue;

            kwargs.handler = kwargs.handler ? kwargs.handler : new FileEventHandler();

            kwargs.handler->setPath(fni->FileName);
            do {
                std::wstring fileName(fni->FileName, fni->FileNameLength / sizeof(WCHAR));
                switch (fni->Action) {
                    case FILE_ACTION_ADDED: kwargs.handler->added(); break;
                    case FILE_ACTION_REMOVED: kwargs.handler->removed(); break;
                    case FILE_ACTION_MODIFIED: kwargs.handler->modified(); break;
                    case FILE_ACTION_RENAMED_OLD_NAME: kwargs.handler->renamedOld(); break;
                    case FILE_ACTION_RENAMED_NEW_NAME: kwargs.handler->renamedNew(); break;
                }
                fni = fni->NextEntryOffset ? reinterpret_cast<FILE_NOTIFY_INFORMATION*>(reinterpret_cast<BYTE*>(fni) + fni->NextEntryOffset) : nullptr;
            } while (fni);
            getRecentFileChangeLog();
        }
    }
    CloseHandle(hDir);
}

SERVICE_STATUS_HANDLE g_ServiceStatusHandle = nullptr;
SERVICE_STATUS g_ServiceStatus              = {0};

// void getRecentFileChangeLog() {
//     HANDLE hEventLog = OpenEventLog(nullptr, TEXT("Security"));
//     if (hEventLog == nullptr) {
//         warn("Could not open event log", RuntimeWarning);
//         return;
//     }
//
//     DWORD bytesNeeded = 0;
//     DWORD eventsRead = 0;
//     DWORD totalEvents = 0;
//
//     if (!ReadEventLog(hEventLog, EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ, 0, nullptr, 0, &bytesNeeded, &totalEvents)) {
//         auto lastError = GetLastError();
//         if (lastError != ERROR_INSUFFICIENT_BUFFER) {
//             warn("Error reading event log(first call) -- " + std::to_string(lastError), RuntimeWarning);
//             CloseEventLog(hEventLog);
//             return;
//         }
//     }
//     auto *buffer = new BYTE[bytesNeeded];
//
//     if (!ReadEventLog(hEventLog, EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ, 0, buffer, bytesNeeded, &bytesNeeded, &eventsRead)) {
//         warn("Error reading event log(second call) -- " + std::to_string(GetLastError()), RuntimeWarning);
//         delete[] buffer;
//         CloseEventLog(hEventLog);
//         return;
//     }
//
//     auto *pRecord = (EVENTLOGRECORD*)buffer;
//     for (DWORD i = 0; i < eventsRead; i++) {
//         if (pRecord->EventID == 4663) {
//             std::cout << "Access Log: " << std::endl;
//             std::cout << "Event ID: " << pRecord->EventID << std::endl;
//         }
//         pRecord = (EVENTLOGRECORD*)((LPBYTE)pRecord + pRecord->Length);
//     }
//
//     delete[] buffer;
//     CloseEventLog(hEventLog);
// }

void getRecentFileChangeLog() {
    // 获取当前线程ID
    DWORD threadId = GetCurrentThreadId();

    // 根据线程ID获取进程ID
    DWORD processId = GetProcessId(GetCurrentProcess());

    // 获取进程句柄
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (hProcess == nullptr) {
        warn(&"Error opening process handle: "[GetLastError()], RuntimeWarning);
        return;
    }

    // 获取进程名称
    TCHAR processName[MAX_PATH] = "Unknown";
    if (GetModuleFileNameEx(hProcess, nullptr, processName, sizeof(processName) / sizeof(TCHAR)))
        std::wcout << L"Recent change by process: " << processName << std::endl;
    else
        warn(&"Could not retrieve process name: "[GetLastError()], RuntimeWarning);

    TCHAR username[256] = "Unknown";
    DWORD usernameSize  = sizeof(username) / sizeof(TCHAR);
    if (!GetUserName(username, &usernameSize)) warn(&"Error getting username: "[GetLastError()], RuntimeWarning);

    std::wcout << L"Recent change by user: " << username << " at process: " << processName << std::endl;

    CloseHandle(hProcess);
}

void reportServiceStatus(DWORD state, DWORD exitCode, DWORD waitHint) {
    g_ServiceStatus.dwServiceType      = SERVICE_WIN32;
    g_ServiceStatus.dwCurrentState     = state;
    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    g_ServiceStatus.dwWin32ExitCode    = exitCode;
    g_ServiceStatus.dwWaitHint         = waitHint;
    SetServiceStatus(g_ServiceStatusHandle, &g_ServiceStatus);
}

void WINAPI serviceMain(DWORD argc, LPTSTR* argv) {
    g_ServiceStatusHandle = RegisterServiceCtrlHandler("FileMonitor", serviceCtrlHandler);

    reportServiceStatus(SERVICE_START_PENDING, NO_ERROR, 3000);

    watch(L"C:\\");

    reportServiceStatus(SERVICE_RUNNING, NO_ERROR, 0);

    Sleep(INFINITE);
}

void WINAPI serviceCtrlHandler(DWORD ctrl) {
    switch (ctrl) {
        case SERVICE_CONTROL_STOP:
            reportServiceStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
            reportServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
            break;
        default: warn("Unknown control code!", RuntimeWarning); break;
    }
}

/**
 * 1. 使用sc.exe命令安装服务：
 * 在管理员命令提示符下执行以下命令：
 * sc create FileMonitorService binPath= "C:\Path\To\Your\Service.exe"
 *
 * 2. 设定自动启动：
 * 你可以设置服务在启动时自动启动：
 * sc config FileMonitorService start= auto
 *
 * 3. 启动服务：
 * sc start FileMonitorService
 * */
// int _tmain(int argc, TCHAR* argv[]) {
//     SERVICE_TABLE_ENTRY serviceTable[] = {
//         { "FileMonitor", (LPSERVICE_MAIN_FUNCTION)serviceMain },
//         { nullptr, nullptr }
//     };
//     StartServiceCtrlDispatcher(serviceTable);
//     return 0;
// }
