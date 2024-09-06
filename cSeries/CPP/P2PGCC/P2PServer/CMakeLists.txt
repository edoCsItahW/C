cmake_minimum_required(VERSION 3.28.1)

project(P2PServer VERSION 1.0)
#project(Server VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../executable)

add_executable(${PROJECT_NAME} server.cpp)
#add_executable(${PROJECT_NAME} P2PServer.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    E:/codeSpace/codeSet/C/cSeries/CPP/P2PGCC/lib/ws2_32.dll
)
