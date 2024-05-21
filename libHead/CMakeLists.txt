cmake_minimum_required(VERSION 3.15)
project(TYPELIB)

option(EXPORT "Export symbols" ON)

if (EXPORT)
    add_compile_definitions(ALLOW_EXPORT)
    add_library(arrLib SHARED ./arrLib_.c)

else()
    add_library(arrLib STATIC ./arrLib_.c)
endif()

target_include_directories(arrLib PUBLIC "E:/codeSpace/codeSet/C/libHead")