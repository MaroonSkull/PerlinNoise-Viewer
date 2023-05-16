# here we add all our code
cmake_minimum_required (VERSION 3.19)
project (${PROJECT_NAME} LANGUAGES CXX)

add_executable (${PROJECT_NAME} "Main.cpp")
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_compile_features (${PROJECT_NAME} PUBLIC cxx_std_17)

#[[include our code
foreach (library ${srcsList})
    add_subdirectory_checked (${CMAKE_CURRENT_SOURCE_DIR}/${library})
endforeach ()]]