cmake_minimum_required(VERSION 3.28.1)

project(P2PServer VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(Server P2PServer.cpp)

# target_link_libraries(MyTestExecutable PRIVATE ${Boost_LIBRARIES})
