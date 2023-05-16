# main cmake file
cmake_minimum_required (VERSION 3.19)
project ("PerlinNoise-Viewer" LANGUAGES CXX)

function(add_subdirectory_checked dir)
    if (NOT EXISTS ${dir}/CMakeLists.txt)
        message(FATAL_ERROR
                "Error: Subdirectory " ${dir} " not found\n"
                "You may have cloned the repository without the --recursive flag\n"
                "Use `git submodule update --init --recursive` to get the required dependencies"
                )
    endif ()
    add_subdirectory(${dir})
endfunction()

# set external dependencies list
# glfwpp has public linkage of glew, glfw & imgui
set (dependenciesList
    OpenGL::GL
    GLFWPP
    libglew_static
    Imgui
    # PerlinNoise-Kernel
)
# set internal sources list
set (ShaderLib "Shader")
set (srcsList
    #${ShaderLib}
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