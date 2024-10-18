cmake_minimum_required(VERSION 3.28.1)

project(P2PServer VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../executable)

include(../../../cmake/jsoncpp.cmake)

add_executable(${PROJECT_NAME}
    server.cpp
    main.cpp
)

#target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../lib/ws2_32.dll)
