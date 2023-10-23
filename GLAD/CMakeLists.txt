cmake_minimum_required(VERSION 3.15)

project(GLADLIB)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC)

message(SRC)

set(LIBRARY_OUTPUT_PATH ${LIB_PATH})

add_library(${GLAD_LIB} STATIC ${SRC})