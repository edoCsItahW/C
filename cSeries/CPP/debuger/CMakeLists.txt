cmake_minimum_required(VERSION 3.28.1)

project(Debuger VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
        test.cpp
        src/debuger.cpp
        src/debuger.hpp
)
