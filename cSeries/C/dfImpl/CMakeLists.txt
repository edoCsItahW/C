cmake_minimum_required(VERSION 3.28.1)

project(DFImpl VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

#target_compile_options(${PROJECT_NAME} PRIVATE -std=c2x)

add_executable(${PROJECT_NAME}
    main.c
)

# 链接lib文件(无论静态库还是动态库)
# 动态库还需确保.dll/.so文件在运行时能够被找到(如复制到${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/st/dfimpl.lib)
