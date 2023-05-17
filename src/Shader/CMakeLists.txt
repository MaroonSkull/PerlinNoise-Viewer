# ShaderLib config
cmake_minimum_required (VERSION 3.19)
project (${PROJECT_NAME} LANGUAGES CXX)

add_library (${ShaderLib} STATIC
	#[[1D/1D.frag
	1D/1D.vert
	1D/1D_noise.vert
	1D/1D_white.vert]]
	${CMAKE_SOURCE_DIR}/include/Shader/Shader.hpp
	Shader.cpp
)


target_include_directories (${ShaderLib} PUBLIC ${CMAKE_SOURCE_DIR}/include/Shader)

target_compile_features (${ShaderLib} PUBLIC cxx_std_17)
target_link_libraries (${ShaderLib} PRIVATE glad)