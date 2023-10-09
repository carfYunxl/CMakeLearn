cmake_minimum_required(VERSION 3.10)

project(app)

set(CMAKE_CXX_STANDARD 17)

set(
    SRC_LIST main.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Printer.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Printer.hpp
    )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(ap SHARED ${SRC_LIST})

# 指定mylib.so的输出路径
set_target_properties(ap PROPERTIES LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(app ${SRC_LIST})