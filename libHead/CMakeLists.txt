cmake_minimum_required(VERSION 3.15)
project(TYPELIB)

option(EXPORT "Export symbols" ON)

if (EXPORT)
    add_compile_definitions(ALLOW_EXPORT)
    add_library(libArray SHARED libArray.c)

else()
    add_library(libArray STATIC libArray.c)
endif()

target_include_directories(libArray PUBLIC "E:/codeSpace/codeSet/C/libHead")