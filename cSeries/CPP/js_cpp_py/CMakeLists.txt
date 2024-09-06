cmake_policy(SET CMP0057 NEW)
# 3.29是你的cmake版本
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
project(bridge VERSION 1.0)  # 大小项目名

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add_compile_options(/wd4819)
#add_compile_options(/wd4715)

include(../../cmake/pybind11.cmake)
include(../../cmake/node.cmake)

#pybind11_add_module(${PROJECT_NAME}
##    js/global.cpp
#    main.cpp
#)  # 两个参数,小写的项目名和主cpp文件名

find_package(V8 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

#set_target_properties(${PROJECT_NAME} PROPERTIES
#    PREFIX ""  # 去掉默认前缀
#    SUFFIX ".pyd"  # 设置后缀为.pyd
#)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/node.lib
    ${CMAKE_SOURCE_DIR}/lib/python311.lib
    ${V8_LIBRARIES}
)
