cmake_minimum_required(VERSION 3.28.1)
project(COMBINE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("E:/codeSpace/codeSet/C/boost.cmake")
include("E:/codeSpace/codeSet/C/pybind11.cmake")

find_package(Python 3.11 COMPONENTS Interpreter Development REQUIRED)
find_package(Boost REQUIRED COMPONENTS python)


add_library(combine MODULE combine.cpp)

target_include_directories(combine PRIVATE ${PYTHON_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
target_link_libraries(combine PRIVATE ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} pybind11::module)

target_link_libraries(combine PRIVATE)

set_target_properties(combine PROPERTIES
        PREFIX ""
        SUFFIX ".pyd"
)
