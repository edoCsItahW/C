cmake_minimum_required(VERSION 3.28.1)

# 项目名
project(DfImpl VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/../../lib/st)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# 库名
set(LIB_NAME "dfimpl")

#add_compile_options(/wd4819)

add_library(${LIB_NAME} STATIC
    dfImpl.h
    dfImpl.c
)

# MSCV: 1. cmake -B build -S . 2. cmake --build build --config Release
# MinGW: 1. mkdir build 2. cd build 3. cmake .. -G "MinGW makefiles" 4. mingw32-make