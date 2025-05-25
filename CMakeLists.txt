# main cmake file
cmake_minimum_required (VERSION 3.19)

project (PNV
  VERSION 1.1
  DESCRIPTION "Perlin noise viewer for [Perlin noise kernel](https://github.com/MaroonSkull/PerlinNoise-Kernel)."
  HOMEPAGE_URL https://github.com/MaroonSkull/PerlinNoise-Kernel
  LANGUAGES C CXX CUDA
)

#include (cmake/prevent_in_source_builds.cmake)
include (cmake/utils.cmake)

# enable CUDA
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
option (USE_CUDA_IF_AVAILABLE "Prefer CUDA if available" ON)

# Check if CUDA is available
include (CheckLanguage)
check_language (CUDA)
if (CMAKE_CUDA_COMPILER AND USE_CUDA_IF_AVAILABLE)
  enable_language (CUDA)
  
  set (CMAKE_CUDA_STANDARD 17)
  set (CMAKE_CUDA_ARCHITECTURES 89)  # sm_89 for Ada Lovelace

  find_package(Thrust REQUIRED CONFIG)
  thrust_create_target(Thrust)
else ()
  message (
    #FATAL_ERROR
    STATUS
    "CUDA not found"
  )
endif ()

# set project options
option (PNV_PREFER_BUNDLED_THIRD_PARTIES "Prefer bundled over system variants of third party libraries" ON)

# include 3rd party libraries & our code
add_subdirectory (dependencies)
add_subdirectory (src)

find_package (OpenGL REQUIRED)

if (TARGET PNK)
  # make alias for compatibility
  add_library (PNK::PNK ALIAS PNK)
else ()
  find_package (PNK CONFIG REQUIRED)
endif ()

# set external dependencies list
# glfwpp has public linkage of glew, glfw & imgui
set (dependenciesList
  OpenGL::GL
  PNK::PNK
  glad
  GLFWPP
  glm::glm
  imgui
  implot
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

unset(USE_CUDA_IF_AVAILABLE CACHE)