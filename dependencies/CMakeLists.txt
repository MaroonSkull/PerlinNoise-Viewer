# here we add all dependencies
cmake_minimum_required (VERSION 3.19)
project (${PROJECT_NAME} LANGUAGES CXX C)

# glad
# required C language
add_library (glad
	glad/include/glad/glad.h
	glad/src/glad.c)

target_include_directories (glad PUBLIC glad/src)
target_include_directories (glad PUBLIC glad/include)


# GLFWPP
# contains imgui + glfw (+ glew)
set(GLFWPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # disable building GLFWPP examples
add_subdirectory_checked (${CMAKE_CURRENT_SOURCE_DIR}/glfwpp)

#PerlinNoise-Kernel
#add_subdirectory (PerlinNoise-Kernel)
