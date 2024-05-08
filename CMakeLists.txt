cmake_minimum_required(VERSION 3.29)
#项目名字
project(test)
#设置编译版本


set(SOURCE_FILES
        ./test.c)


set(ZLIB_INCLUDE E:/ProgramFiles/Anaconda/include)

# 设置项目输出
set(EXECUTABLE_OUTPUT_PATH .)
# 链接外部库
include_directories(${ZLIB_INCLUDE})

# 设置编译文件
add_executable(test ./test.c)
#将第三方库链接在一起
target_link_libraries (${PROJECT_NAME} Python.h)