cmake_minimum_required(VERSION 3.28.1)

project(DoxygenExample VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
    src/example.cpp
)
