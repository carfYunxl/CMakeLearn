# create build directory

```SHELL

    cmake ..
    cmake --build . #Debug版本

    cmake --build . --config Release #Release版本

```

# win32 link static/shared library 
## how to write cmake
```SHELL
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/include)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/dll)

    # this should be here
    add_executable(app ${SRC_LIST} main.cpp)

    link must after add_executable
    target_link_libraries(app glfw3dll)
```

## cmake compile
```SHELL
    cmake "Visual Studio 16 2019" "-A win32" ..
    cmake --build .
```
