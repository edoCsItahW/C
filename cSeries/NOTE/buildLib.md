使用 CMake 和 MinGW 编译动态库和静态库的步骤如下。

### 创建项目结构

首先，创建一个简单的项目结构。假设项目目录为 `MyLibrary`，其中包含如下文件：

```
MyLibrary/
├── CMakeLists.txt
├── src/
│   └── MyLibrary.cpp
└── include/
    └── MyLibrary.h
```

CopyInsert

### 编写库代码

在 `include/MyLibrary.h` 中编写库的头文件：

```cpp
#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

#ifdef MY_LIBRARY_EXPORTS
#define MY_LIBRARY_API __declspec(dllexport)
#else
#define MY_LIBRARY_API __declspec(dllimport)
#endif

class MY_LIBRARY_API MyLibrary {
public:
    void hello();
};

#endif // MY_LIBRARY_H
```

CopyInsert

在 `src/MyLibrary.cpp` 中编写库的实现：

```cpp
#include "MyLibrary.h"
#include <iostream>

void MyLibrary::hello() {
    std::cout << "Hello from MyLibrary!" << std::endl;
}
```

CopyInsert

### 创建 CMakeLists.txt 文件

在 `CMakeLists.txt` 文件中配置构建选项：

```cmake
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(MyLibrary)

# 添加目录包含
include_directories(include)

# 创建静态库
add_library(MyStaticLibrary STATIC src/MyLibrary.cpp)

# 创建动态库
add_library(MyDynamicLibrary SHARED src/MyLibrary.cpp)

# 设置导出宏
target_compile_definitions(MyDynamicLibrary PRIVATE MY_LIBRARY_EXPORTS)
```

CopyInsert

### 编译库

1. 打开命令提示符或终端，导航到 `MyLibrary` 目录。

2. 创建一个构建目录：

   ```bash
   mkdir build
   cd build
   ```

   CopyInsert

3. 使用 CMake 配置项目：

   ```bash
   cmake .. -G "MinGW Makefiles"
   ```

   CopyInsert

4. 编译项目：

   ```bash
   mingw32-make
   ```

   CopyInsert

### 结果

在 `build` 目录中，你应该能够找到生成的库文件：

- `MyStaticLibrary.a`：静态库。
- `MyDynamicLibrary.dll`：动态库。

### 使用库

在你的主程序中，你可以链接这两个库并使用它们提供的功能。确保在链接时正确指定库的路径和链接选项。

这是一个简单的示例，演示了如何使用 CMake 和 MinGW 创建静态库和动态库的过程。你可以根据项目的实际需求进行相应的调整。