cmake_policy(SET CMP0057 NEW)

cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
project(WINDOWSAPI)

find_package(Python 3.11 COMPONENTS Interpreter Development
        REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
pybind11_add_module(windowsApi windowsApi.cpp)
