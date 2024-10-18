cmake_minimum_required(VERSION 3.28.1)

project(QuesParser VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(/wd4819)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "E:/codeSpace/codeSet/Python/privateProject/quesParser")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(pybind11_DIR "E:/ProgramFiles/Anaconda/Lib/site-packages/pybind11/share/cmake/pybind11")

# 3.11是你的python解释器版本
find_package(Python 3.11 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(${PROJECT_NAME}
        build.cpp
        lexer/lexer.cpp
        parser/parser.cpp
        exception/exception.cpp
)  # 两个参数,小写的项目名和主cpp文件名

