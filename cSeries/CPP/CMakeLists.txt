cmake_minimum_required(VERSION 3.28.0)

project(test VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} test.cpp)
