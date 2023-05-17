# main cmake file
cmake_minimum_required (VERSION 3.19)
project ("PerlinNoise-Viewer" LANGUAGES CXX)

include(cmake/utils.cmake)

# set external dependencies list
# glfwpp has public linkage of glew, glfw & imgui
set (dependenciesList
    OpenGL::GL
    glad
    GLFWPP
    imgui
    #PerlinNoise-Kernel
)
# set internal sources list
set (ShaderLib "Shader")
set (srcsList
    ${ShaderLib}
)

# include OpenGL
find_package (OpenGL REQUIRED)

# include 3rd party libraries & our code
add_subdirectory_checked (${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
add_subdirectory_checked (${CMAKE_CURRENT_SOURCE_DIR}/src)

# link libraries
foreach (library ${dependenciesList} ${srcsList})
    target_link_libraries (${PROJECT_NAME} PUBLIC ${library})
endforeach ()