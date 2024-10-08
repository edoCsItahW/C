cmake_minimum_required(VERSION 3.28.1)

project(VarLex VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(${PROJECT_NAME}
    interpreter/parser/node.cpp
    exception/exception.cpp
    interpreter/parser/node.tpp
    interpreter/parser/parser.cpp
    interpreter/lexer/lexer.cpp
    main.cpp
)
