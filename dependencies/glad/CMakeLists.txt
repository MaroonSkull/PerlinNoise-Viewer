# glad config, use C language
cmake_minimum_required (VERSION 3.19)
project (${PROJECT_NAME} LANGUAGES C)

# glad
add_library (glad
	${CMAKE_CURRENT_SOURCE_DIR}/glad/include/glad/gl.h
	${CMAKE_CURRENT_SOURCE_DIR}/glad/src/gl.c
)

target_include_directories (glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)