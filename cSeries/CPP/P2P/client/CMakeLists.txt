cmake_minimum_required(VERSION 3.28.1)

project(P2PClient VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../executable)

include(../../../cmake/jsoncpp.cmake)

include_directories("E:/codeSpace/codeSet/C/cSeries/CPP/debuger/src")

add_executable(${PROJECT_NAME}
        ../lib/proto.cpp
        ../lib/proto.hpp
        client.cpp
        main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32
        "E:/codeSpace/codeSet/C/cSeries/CPP/debuger/lib/libDebugger_st_MINGW.a"
)