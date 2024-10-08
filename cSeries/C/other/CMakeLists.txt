cmake_minimum_required(VERSION 3.28.1)

project(tmp VERSION 1.0)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)


add_executable(${PROJECT_NAME} practice.c)

# target_link_libraries(MyTestExecutable PRIVATE ${Boost_LIBRARIES})
