cmake_minimum_required(VERSION 3.28.1)

project(QuesParser VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_NAME} "E:/codeSpace/codeSet/C/cSeries/CPP/conFunc/src")

add_executable(${PROJECT_NAME}
    main.cpp
    src/exception/exception.cpp
    src/parser/parser.cpp
    src/lexer/lexer.cpp
)

#target_link_libraries(${PROJECT_NAME} PRIVATE "E:/codeSpace/codeSet/C/cSeries/CPP/conFunc/lib/confunc_MSCV.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE "E:/codeSpace/codeSet/C/cSeries/CPP/conFunc/lib/libconfunc_MINGW.a")
