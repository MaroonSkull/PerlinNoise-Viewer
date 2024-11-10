# here we add all dependencies
cmake_minimum_required (VERSION 3.19)
project (${PROJECT_NAME} LANGUAGES CXX)

#glad
add_subdirectory_checked(${CMAKE_CURRENT_SOURCE_DIR}/glad)

# GLFWPP
set(GLFWPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # disable building examples
add_subdirectory_checked (${CMAKE_CURRENT_SOURCE_DIR}/glfwpp)

#imgui
add_subdirectory_checked (${CMAKE_CURRENT_SOURCE_DIR}/imgui)

#PerlinNoise-Kernel
# This is bundled so we don't need to install it
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/PerlinNoise-Kernel)
