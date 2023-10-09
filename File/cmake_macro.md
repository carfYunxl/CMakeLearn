# CMake常用宏命令

----------------------------------------

## 1 、预定义宏

- **PROJECT_SOURCE_DIR**  ： 工程的根目录

- **PROJECT_BINARY_DIR**  ： 保存MAKEFILE临时文件的目录

- **PROJECT_NAME**        ： project命令定义的名称

``` CMake
    cmake_minimum_required(VERSION 3.12)

    #定义project的名称为app
    project(app)

    add_executable(app main.cpp)

```

```C++

    #include <iostream>

    int main()
    {
        std::cout << "Example code block!" << std::endl;
        return 0;
    }

```

- **CMAKE_CURRENT_SOURCE_DIR**    ：CMakeLists.txt所在的路径

- **CMAKE_CURRENT_BINARY_DIR**    ：targer编译目录

- **CMAKE_CURRENT_LIST_DIR**      ：CMakeLists.txt完整路径

- **EXECUTABLE_OUTPUT_PATH**         ：指定可执行文件保存的路径

- **LIBRARY_OUTPUT_PATH**         ：保存动态库/静态库的保存路径

## 2、系统信息

- **CMAKE_MAJOR_VERSION**         : cmake主版本

- **CMAKE_MINOR_VERSION**         ：cmake次版本号

- **CMAKE_PATCH_VERSION**         ：cmake补丁等级，比如3.4.1中的1

- **CMAKE_SYSTEM**                : 系统名称，比如 **Linux-2.6.22**

- **CMAKE_SYSTEM_NAME**           : 不包含版本的系统名称，如 **Linux**

- **UNIX**                        : 所有类UNIX平台，其值TRUE

- **WIN32**                       ：WIN32平台，其值为TRUE

## 3、主要开关选项

- **BUILD_SHARED_LIBS**           : 设为ON将输出动态库

```cmake

    #if set like this, add_library() 可不指明 SHARED 也可产出动态库
    set(BUILD_SHARED_LIBS ON)

```
