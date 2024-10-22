cmake_minimum_required(VERSION 3.28.1)

# 项目名
project(Debuger VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 生成位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# 库名
set(LIB_NAME "Debuger_dy_MINGW")

#add_compile_options(/wd4819)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_library(${LIB_NAME} SHARED
    debuger.h
    debuger.hpp
    debuger.cpp
)

# 如有链接动态库(dll)需补全(如: ws2_32.dll -> ws2_32)
#target_link_libraries(${LIB_NAME} PRIVATE )

# 导出宏
target_compile_definitions(${LIB_NAME} PRIVATE DLL_BUILD)

# MSCV: 1. cmake -B build -S . 2. cmake --build build --config Release
# MinGW: 1. mkdir build 2. cd build 3. cmake .. -G "MinGW makefiles" 4. mingw32-make