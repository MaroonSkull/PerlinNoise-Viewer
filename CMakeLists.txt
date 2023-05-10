# main cmake file
cmake_minimum_required (VERSION 3.19)
project ("PerlinNoise-Viewer" LANGUAGES CXX)

set (SHADERS_DIR "Shaders")

#include OpenGL
find_package (OpenGL REQUIRED)

#include 3rd party libraries
add_subdirectory ("dependencies")

#include our code
add_subdirectory ("src")

#link libraries
foreach (library OpenGL::GL imgui )#PerlinNoise-Kernel)
    target_link_libraries (${PROJECT_NAME} PRIVATE ${library})
endforeach ()