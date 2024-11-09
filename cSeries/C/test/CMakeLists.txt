cmake_minimum_required(VERSION 3.28.1)

project(Test VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
        main.c
)
