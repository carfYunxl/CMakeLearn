cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

project(GEditor)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Scene  SceneSRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Panels PanelSRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GLAD/src SRC_GLAD)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/stb SRC_STB)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/imgui IMGUI_SRC1)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends IMGUI_SRC2)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/entt/include ENTT_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo ImGuizmo_SRC)

set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Scene)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Panels)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/stb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLAD/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/entt/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/lib)

link_libraries(glfw3.lib opengl32.lib yaml-cpp.lib)

add_executable(GEditor ${SRC} ${SRC_STB} ${IMGUI_SRC1}  ${IMGUI_SRC2} ${SRC_GLAD} ${ENTT_SRC} ${SceneSRC} ${PanelSRC} ${ImGuizmo_SRC} GL_EditorLayer.h GL_EditorLayer.cpp GL_App.cpp )