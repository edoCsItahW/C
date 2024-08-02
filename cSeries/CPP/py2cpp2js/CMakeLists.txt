cmake_minimum_required(VERSION 3.28.1)

project(bridge VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(../../cmake/pybind11.cmake)
include(../../cmake/node.cmake)

add_executable(bridge bridging.cpp)
