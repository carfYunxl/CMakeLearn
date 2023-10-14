# create build directory

```SHELL

    cmake ..
    cmake --build . #Debug版本

    cmake --build . --config Release #Release版本

```

# win32 link static/shared library ，use glfw as example
use glfw as example, you can download it's binnary file like below:
- glfw3.h
- glfw3_native.h
- glfw3.lib
- glfw3dll.lib
- glfw3.dll

glfw3.lib is static library, you can use header file and glfw3.lib to static linkage

if you want to dynamic link, use cmake to link glfw3dll.lib, and put glfw3.dll to executable folder, then it will work!

## how to write cmake
```SHELL
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/include)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/dll)

    # this should be here
    add_executable(app ${SRC_LIST} main.cpp)

    link must after add_executable

    // if use static library, you should write like this:
    target_link_libraries(app glfw3)

    // but if you use shared library, you should write like this:
    target_link_libraries(app glfw3dll)
```

## cmake compile
```SHELL
    cmake "Visual Studio 16 2019" "-A win32" ..
    cmake --build .
```
