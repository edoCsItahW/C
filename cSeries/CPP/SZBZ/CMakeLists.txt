cmake_minimum_required(VERSION 3.28.1)

project(szbz VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(../../cmake/jsoncpp.cmake)

add_executable(${PROJECT_NAME}
    ${JSONCPP_INCLUDE_DIR}/jsoncpp.cpp
    src/cls/tianGan.cpp
    src/cls/siZhu.cpp
    src/cls/ganZhi.cpp
    src/global.cpp
    main.cpp
)
