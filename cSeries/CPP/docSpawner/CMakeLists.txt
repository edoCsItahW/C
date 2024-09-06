cmake_policy(SET CMP0057 NEW)
# 3.29是你的cmake版本
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
project(docSpawner VERSION 1.0 LANGUAGES CXX)  # 大小项目名

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

include(../../cmake/pybind11.cmake)

add_executable(${PROJECT_NAME}
        bin/include/jsoncpp.cpp
        bin/docSp.cpp
        main.cpp
)

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/bin/lib/python311.lib)
