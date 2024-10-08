cmake_minimum_required(VERSION 3.28.1)

project(DFImpl VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

#target_compile_options(${PROJECT_NAME} PRIVATE -std=c2x)

add_executable(${PROJECT_NAME}
    dfImpl.c
    main.c
)
