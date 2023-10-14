cmake_minimum_required(VERSION 3.15)

project(app)

set(CMAKE_CXX_STANDARD 17)

# 1 list all source file
# set(
#     SRC_LIST main.cpp 
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/Printer.cpp 
#     )

# 2 find file use aux_source_directory
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

# 3 使用file指令查找文件
#file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include2)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/include)

# add_library(apShared SHARED ${SRC_LIST})
# add_library(apStatic STATIC ${SRC_LIST})

# 指定ap.dll的输出路径
# set_target_properties(apShared PROPERTIES LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

#包含动态/静态库所在的文件路径
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/lib)
#链接静态库
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/lib/)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set(BUILD_SHARED_LIBS TRUE)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/dll)

add_executable(app ${SRC_LIST} main.cpp)

target_link_libraries(app glfw3dll)