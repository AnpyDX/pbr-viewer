# PBRV external configuration

## GLAD
set(EXTERNAL_GLAD ${CMAKE_CURRENT_SOURCE_DIR}/glad CACHE INTERNAL "glad root directory")

## GLFW
set(BUILD_SHARED_LIBS   OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS    OFF)
set(GLFW_BUILD_DOCS     OFF)
set(GLFW_INSTALL        OFF)
add_subdirectory("glfw")

## bmx
add_subdirectory("bmx")

## assimp
add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_subdirectory("assimp")

## imgui
set(EXTERNAL_IMGUI ${CMAKE_CURRENT_SOURCE_DIR}/imgui CACHE INTERNAL "imgui root directory")

## mas
set(EXTERNAL_MAS ${CMAKE_CURRENT_SOURCE_DIR}/mas CACHE INTERNAL "mas root directory")

## font-cpp
set(EXTERNAL_FONTCPP ${CMAKE_CURRENT_SOURCE_DIR}/fontcpp CACHE INTERNAL "fontcpp root directory")

## stb
set(EXTERNAL_STB ${CMAKE_CURRENT_SOURCE_DIR}/stb CACHE INTERNAL "stb root directory")

## json
set(EXTERNAL_JSON ${CMAKE_CURRENT_SOURCE_DIR}/json CACHE INTERNAL "json root directory")
