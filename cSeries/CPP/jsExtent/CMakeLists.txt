cmake_minimum_required(VERSION 3.28.1)

project(EXTENT VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Node_DIR "C:/Users/Lenovo/AppData/Local/node-gyp/Cache/20.12.2")
set(Node_INCLUDE_DIRS ${Node_DIR}/include/node)
set(NAPI_INCLUDE_DIRS "D:/ProgramFiles/CACHE/pnpm/global/5/node_modules/node-addon-api")

include_directories(${Node_INCLUDE_DIRS} ${NAPI_INCLUDE_DIRS})

add_executable(jsExtent extent.cpp)

target_link_libraries(jsExtent PRIVATE ${Node_DIR}/x64/node.lib)
