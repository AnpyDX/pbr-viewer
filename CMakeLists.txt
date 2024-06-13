# PBR-Viewer CMakeProject
cmake_minimum_required(VERSION 3.8)

project("PBR-Viewer")

set(CMAKE_CXX_STANDARD 17)

# add source to project
add_subdirectory("thirdparty")
aux_source_directory(${EXTERNAL_IMGUI_DIR}/include/imgui IMGUI_SOURCES)
set(
    PBRV_SOURCES
    include/core/framebuffer.cxx
    include/core/indexbuffer.cxx
    include/core/vertexbuffer.cxx
    include/core/shader.cxx
    include/core/texture.cxx
    
    include/camera.cxx
)

add_executable(
    "PBR-Viewer"
    src/main.cpp
    ${PBRV_SOURCES}
    ${IMGUI_SOURCES}
    ${EXTERNAL_GLAD_DIR}/src/glad.c
)

# add include directorie
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${EXTERNAL_GLAD_DIR}/include
    ${EXTERNAL_STB_DIR}/include
    ${EXTERNAL_MAS_DIR}/include
    ${EXTERNAL_IMGUI_DIR}/include
    ${EXTERNAL_FONTCPP_DIR}/include
)

# link libraries 
if(WIN32)
    target_link_libraries(
        "PBR-Viewer" glfw bmx opengl32
    )
elseif(UNIX)
    target_link_libraries(
        "PBR-Viewer" glfw bmx GL X11 Xrandr Xi
    )
else()
    message(FATAL_ERROR "Project does not support current platform!")
endif()