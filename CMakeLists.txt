cmake_minimum_required (VERSION 3.19)
project ("PerlinNoise-Viewer" LANGUAGES CXX)

add_executable (${PROJECT_NAME} "src/Main.cpp")
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set (ENTITIES_DIR "Entities")
set (SERVICES_DIR "Services")
set (SHADERS_DIR "Shaders")

#include OpenGL
find_package (OpenGL REQUIRED)

#include 3rd party libraries
add_subdirectory ("dependencies")

#link libraries
foreach (library OpenGL::GL imgui)
    target_link_libraries (${PROJECT_NAME} PRIVATE ${library})
endforeach ()

# include code
add_subdirectory ("src")

foreach (library ${ENTITIES_DIR} ${SERVICES_DIR} ${SHADERS_DIR})
    target_link_libraries (${PROJECT_NAME} PRIVATE ${library})
endforeach ()