cmake_policy(SET CMP0057 NEW)
# 3.29是你的cmake版本
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
project(LINKEDLIST)

# 3.11是你的python解释器版本
find_package(Python 3.11 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(linkedList linkedList.cpp)
