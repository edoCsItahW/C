cmake_policy(SET CMP0057 NEW)
# 3.29是你的cmake版本
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
project(DfImpl VERSION 1.0.0 LANGUAGES CXX)  # 大小项目名

set(pybind11_DIR "E:/ProgramFiles/Anaconda/Lib/site-packages/pybind11/share/cmake/pybind11")

# 3.11是你的python解释器版本
find_package(Python 3.11 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(${PROJECT_NAME} build.cpp ${CMAKE_SOURCE_DIR}/st/dfImpl.c)  # 两个参数,小写的项目名和主cpp文件名