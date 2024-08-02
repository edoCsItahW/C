# python - C拓展步骤


## C文件编写
   ```C
   #include <pybind11/pybind11.h>
   
   
   int add(int i, int j) {
       return i + j;
   }
   
   
   PYBIND11_MODULE(pyExtent, m) {
       m.def("add", &add, "A function which adds two numbers");
   }
   ```


## 新建并更改`CMakeLists.txt`文件
* <mark>如果cmake版本不对大概会出现[if given arguments](https://blog.csdn.net/weixin_46222091/article/details/105015962)的问题</mark>

   ```cmake
   cmake_policy(SET CMP0057 NEW)
   # 3.29是你的cmake版本
   cmake_minimum_required(VERSION 3.29 FATAL_ERROR)  
   project()  # 大小项目名  
   
   set(pybind11_DIR "E:/ProgramFiles/Anaconda/Lib/site-packages/pybind11/share/cmake/pybind11")
   
   # 3.11是你的python解释器版本
   find_package(Python 3.11 COMPONENTS Interpreter Development REQUIRED)
   find_package(pybind11 CONFIG REQUIRED)
    
   pybind11_add_module()  # 两个参数,小写的项目名和主cpp文件名
   ```


## 运行指令

1. 打开cmd,进入C文件所在目录: `cd \path\to\your`

2. 运行命令: 
   ```dos
   cmake -B build -S .
   ```

3. 检查指令是否正确,并且是否生成了build文件夹,接着将你的C文件改成`.cpp`后缀,还有CMakeLists.txt中的`.c`也改成`.cpp`

   * <mark>如果不更改后缀大概会报出`Error in C++ Standard Library usage [*** .vcxproj]`</mark>

4. 接着运行:
   ```dos
   cmake --build build --config Release
   ```

5. 别忘了将后缀改回来 


## 链接

[pybind11 文档](https://pybind11.readthedocs.io/en/stable/compiling.html)

[知乎CMake指南](https://zhuanlan.zhihu.com/p/371257515)

[CMake 官网](https://cmake.org/)