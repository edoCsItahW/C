cmake_minimum_required(VERSION 3.28.1)

project(mysql VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_GENERATOR_PLATFORM "x64")


include_directories("C:/Program Files/MySQL/MySQL Server 8.0/include")

add_executable(${PROJECT_NAME} main.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/lib/libmysql.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/lib/libmysql.lib DESTINATION ${CMAKE_BINARY_DIR})

set(ENV{PATH} "$ENV{PATH};${CMAKE_SOURCE_DIR}/lib")

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/libmysql.lib
    ${CMAKE_SOURCE_DIR}/lib/libmysql.dll
)
