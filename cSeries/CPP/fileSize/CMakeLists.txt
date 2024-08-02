cmake_minimum_required(VERSION 3.28.1)

project(FILESIZE VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -03")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_executable(fileSize fileSize.cpp)

set(TARGET fileSize)

#include("E:/codeSpace/codeSet/C/boost.cmake")
include("E:/codeSpace/codeSet/C/pybind11.cmake")

#find_package(Boost COMPONENTS REQUIRED filesystem)
find_package(Python 3.11 COMPONENTS Interpreter Development REQUIRED)


link_directories(${Python_LIBRARY_DIRS})

target_link_libraries(${TARGET} PUBLIC ${Boost_LIBRARIES} ${Python_LIBRARIES})
