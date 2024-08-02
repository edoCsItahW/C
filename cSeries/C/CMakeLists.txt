cmake_minimum_required(VERSION 3.15)
project(test)

# 添加Python头文件的包含路径
include_directories("E:/ProgramFiles/Anaconda/include")

# 其他CMake配置...

add_executable(test ./test/practice.c
               ./py.c)

# 如果你还需要链接到Python库（比如嵌入Python解释器），你可能还需要添加link_directories()和target_link_libraries()
# link_directories("E:/ProgramFiles/Anaconda/libs")  # 注意：通常不建议使用link_directories，因为它可能导致链接器搜索路径的混乱
target_link_libraries(test "E:/ProgramFiles/Anaconda/libs/python311.lib")  # 替换XY为你的Python版本号