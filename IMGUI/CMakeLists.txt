cmake_minimum_required(VERSION 3.15)

project(IMGUILIB)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/IMGUI)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

set(LIBRARY_OUTPUT_PATH ${LIB_PATH})

add_library(${IMGUI_LIB} STATIC ${SRC})