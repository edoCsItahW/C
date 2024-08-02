cmake_minimum_required(VERSION 3.28.1)

project(MYSQLAPI VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_PREFIX_PATH "E:/ProgramFiles/cppPackage/sqlConnectorCpp9")

#find_package(mysql-concpp REQUIRED)

include_directories("E:/ProgramFiles/cppPackage/sqlConnectorCpp9/include")
link_directories("E:/ProgramFiles/cppPackage/sqlConnectorCpp9/lib64")


add_executable(mysqlAPI mysqlAPI.cpp)

target_link_libraries(mysqlAPI
        "E:/ProgramFiles/cppPackage/sqlConnectorCpp9/lib64/vs14/mysqlcppconn.lib"
)

target_link_libraries(mysqlAPI
        "E:/ProgramFiles/cppPackage/sqlConnectorCpp9/lib64/vs14/mysqlcppconnx.lib"
)

add_custom_command(TARGET mysqlAPI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "E:/ProgramFiles/cppPackage/sqlConnectorCpp9/lib64/vs14/mysqlcppconn.lib"
        $<TARGET_FILE_DIR:mysqlAPI>/mysqlcppconn.lib)

add_custom_command(TARGET mysqlAPI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "E:/ProgramFiles/cppPackage/sqlConnectorCpp9/lib64/vs14/mysqlcppconnx.lib"
        $<TARGET_FILE_DIR:mysqlAPI>/mysqlcppconnx.lib)
