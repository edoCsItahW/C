cmake_minimum_required(VERSION 3.28.1)

project(bridging VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(/wd4819)
add_compile_options(/wd4715)

include_directories(${CMAKE_JS_INC})
#file(GLOB SOURCE_FILES "*.cpp")
#file(GLOB SOURCE_FILES "./py/*.cpp")


add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC}
    main.cpp
    py/type/PyObject.cpp
    py/type/PyType.cpp
    py/global.cpp
)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB}
        ${CMAKE_SOURCE_DIR}/lib/python311.lib
        ${CMAKE_SOURCE_DIR}/lib/node.lib
)

include(./cmake/pybind11.cmake)
include(./cmake/node.cmake)

execute_process(
        COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
)

# 指定生成的.node文件输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ./js)

string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})


add_definitions(-DNAPI_VERSION=4)
