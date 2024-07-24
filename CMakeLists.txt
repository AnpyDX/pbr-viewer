## PBRV project
cmake_minimum_required(VERSION 3.5)
project("PBRV")

set(CMAKE_CXX_STANDARD 17)

# config thirdparty
add_subdirectory("thirdparty")
aux_source_directory(${EXTERNAL_IMGUI}/include/imgui IMGUI_SOURCE)

# add sources
add_executable(
        ${CMAKE_PROJECT_NAME}
        ${EXTERNAL_GLAD}/src/gl.c
        ${IMGUI_SOURCE}

        src/main.cxx
        include/core/indexbuffer.cxx
        include/core/vertexbuffer.cxx
        include/core/framebuffer.cxx
        include/core/texture.cxx
        include/core/shader.cxx
        include/SceneManager.cxx
        include/Camera.cxx
        include/Model.cxx
        include/Light.cxx
        include/SkyBox.cxx
)

# headers & libraries
target_include_directories(
        ${CMAKE_PROJECT_NAME} PRIVATE
        include
        ${EXTERNAL_GLAD}/include
        ${EXTERNAL_MAS}/include
        ${EXTERNAL_IMGUI}/include
        ${EXTERNAL_FONTCPP}/include
        ${EXTERNAL_STB}/include
        ${EXTERNAL_JSON}/include
)

if (WIN32)
    target_link_libraries(
        ${CMAKE_PROJECT_NAME} glfw bmx assimp opengl32
    )
elseif (UNIX)
    target_link_libraries(
        ${CMAKE_PROJECT_NAME} glfw bmx assimp GL X11 Xrandr Xi
    )
else()
    message(FATAL_ERROR "current platform is not supported!")
endif()