cmake_minimum_required(VERSION 3.28.1)

project(Latex VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CMAKE_PREFIX_PATH )

# find_package()

# include_directories()
# link_directories()

add_executable(${PROJECT_NAME}
        src/lexer.cpp
        main.cpp
)

# target_link_libraries(MyTestExecutable PRIVATE ${Boost_LIBRARIES})
