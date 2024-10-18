cmake_minimum_required(VERSION 3.28.1)

project(ProtoDll VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LIB_NAME "proto")

#add_compile_options(/wd4819)
#add_compile_options(/wd4273)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(../../../cmake/jsoncpp.cmake)

# 编译动态库时打开
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

#add_library(${LIB_NAME} STATIC
#    proto.h
#    proto.cpp
#)

add_library(${LIB_NAME} SHARED
    proto.h
    proto.cpp
    jsoncpp.cpp
)

# 仅动态库需要设置
target_link_libraries(${LIB_NAME} PRIVATE ws2_32)

# 仅动态库需要设置
target_compile_definitions(${LIB_NAME} PRIVATE LIB)
