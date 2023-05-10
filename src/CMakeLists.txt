# here we add all our code
cmake_minimum_required (VERSION 3.19)
project (${PROJECT_NAME} LANGUAGES CXX)

add_executable (${PROJECT_NAME} "Main.cpp")
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

#include our code
#add_subdirectory (${SHADERS_DIR})