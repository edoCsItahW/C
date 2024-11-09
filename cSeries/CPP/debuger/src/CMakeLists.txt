cmake_minimum_required(VERSION 3.28.1)

# 项目名
project(Debugger VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 生成位置
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# 库名
set(LIB_NAME "Debugger_st_MINGW")

#add_compile_options(/wd4819)

add_library(${LIB_NAME} STATIC
    debuger.h
    debuger.hpp
    debuger.cpp
)

# MSCV: 1. cmake -B build -S . 2. cmake --build build --config Release
# MinGW: 1. mkdir build 2. cd build 3. cmake .. -G "MinGW makefiles" 4. mingw32-make