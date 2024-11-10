# main cmake file
cmake_minimum_required (VERSION 3.19)

project (PNV
    VERSION 1.0.1
    DESCRIPTION "Perlin noise viewer for [Perlin noise generator](https://github.com/MaroonSkull/PerlinNoise-Kernel)."
    HOMEPAGE_URL https://github.com/MaroonSkull/PerlinNoise-Kernel
    LANGUAGES CXX
)

include(cmake/utils.cmake)

# include 3rd party libraries & our code
add_subdirectory_checked (${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
add_subdirectory_checked (${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package (OpenGL REQUIRED)

# TODO: this solution is only for installed version, need to add bundled.
find_package (PNK REQUIRED)

# set external dependencies list
# glfwpp has public linkage of glew, glfw & imgui
set (dependenciesList
    OpenGL::GL
    PNK::PNK
    glad
    GLFWPP
    imgui
)

# link libraries
foreach (library ${dependenciesList})
    target_link_libraries (${PROJECT_NAME} PUBLIC ${library})
endforeach ()

# set internal sources list
set (ShaderLib "assets/glsl/1D")
set (srcsList
    ${ShaderLib}
)