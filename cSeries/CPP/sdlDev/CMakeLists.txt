cmake_minimum_required(VERSION 3.28.1)

project(SDLDEV VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(CMAKE_PREFIX_PATH "E:/ProgramFiles/cppPackage/SDL2/mingw32")

find_package(SDL2 REQUIRED)

include_directories("E:/ProgramFiles/cppPackage/SDL2/mingw32/include/SDL2")

link_directories("E:/ProgramFiles/cppPackage/SDL2/mingw32/lib")

add_executable(sdlDev test.cpp)

target_link_libraries(sdlDev
    "E:/ProgramFiles/cppPackage/SDL2/mingw32/bin/SDL2.dll"
)

add_custom_command(TARGET sdlDev POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "E:/ProgramFiles/cppPackage/SDL2/mingw32/bin/SDL2.dll"
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE_DIR:sdlDev>)
