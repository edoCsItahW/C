cmake_minimum_required(VERSION 3.28.1)

project(uploadTools VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

add_executable(upload
    global.cpp
    main.cpp
)
