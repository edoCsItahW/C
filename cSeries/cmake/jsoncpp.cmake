# 使用jsoncpp

# 检查jsoncpp的头文件是否存在
if (NOT JSONCPP_INCLUDE_DIR)
    set(JSONCPP_INCLUDE_DIR "E:/ProgramFiles/cppPackage/jsoncpp")
endif ()

include_directories("${JSONCPP_INCLUDE_DIR}")
MESSAGE(STATUS "jsoncpp.cmake <JSONCPP_INCLUDE_DIR>: ${JSONCPP_INCLUDE_DIR}")
