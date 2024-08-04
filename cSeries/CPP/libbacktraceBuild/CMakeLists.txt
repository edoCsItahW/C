cmake_minimum_required(VERSION 3.10)
project(libbacktrace)

# 添加libbacktrace源文件
file(GLOB LIBBACKTRACE_SOURCES "*.c")

# 添加库
add_library(backtrace STATIC ${LIBBACKTRACE_SOURCES})

# 设置安装路径
set(CMAKE_INSTALL_PREFIX ""E:/ProgramFiles/cppPackage/libTrace"")

# 安装库和头文件
install(TARGETS backtrace DESTINATION lib)
install(FILES backtrace.h DESTINATION include)
