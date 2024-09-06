cmake_minimum_required(VERSION 3.28.1)

project(reactive VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
#    src/reactive.cpp
    main.cpp
)
