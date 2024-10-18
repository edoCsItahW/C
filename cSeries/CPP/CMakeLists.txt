cmake_minimum_required(VERSION 3.28.0)

project(test VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("E:/codeSpace/codeSet/C/cSeries/CPP/conFunc/src")

add_executable(${PROJECT_NAME} test.cpp)

target_link_libraries(${PROJECT_NAME} "E:/codeSpace/codeSet/C/cSeries/CPP/conFunc/lib/libconfunc_MINGW.a")
