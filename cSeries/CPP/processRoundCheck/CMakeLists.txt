cmake_minimum_required(VERSION 3.28.1)

project(ProcessRoundCheck VERSION 1.0)

#set(CMAKE_C_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(processRoundCheck
        processRoundCheck.c
        exception.h
)

# find_package(Boost REQUIRED COMPONENTS system)
# target_link_libraries(MyTestExecutable PRIVATE ${Boost_LIBRARIES})
