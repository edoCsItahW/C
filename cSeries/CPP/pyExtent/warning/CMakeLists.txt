cmake_policy(SET CMP0057 NEW)

cmake_minimum_required(VERSION 3.28.1 FATAL_ERROR)
project(WARNING)

set(pybind11_DIR "E:/ProgramFiles/Anaconda/Lib/site-packages/pybind11/share/cmake/pybind11")

find_package(Python 3.11 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
pybind11_add_module(warning warning.cpp)
