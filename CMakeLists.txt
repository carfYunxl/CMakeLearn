cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

project(app)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(GLAD_LIB glad)
add_subdirectory(glad)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLAD/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLAD/include/KHR/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(app ${SRC_LIST} Application.cpp)

target_link_libraries(app glfw3 opengl32 glad)