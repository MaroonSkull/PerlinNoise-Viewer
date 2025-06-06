# here we add all dependencies

#glad
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/glad)

# GLFWPP
set (GLFWPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # disable building examples
add_subdirectory_checked (${CMAKE_CURRENT_SOURCE_DIR}/glfwpp)

# glm
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/glm)

# imgui
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/imgui)

# implot
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/implot)

# implot3d
set(IMPLOT3D_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/implot3d)
set(IMPLOT3D_SOURCE
    ${IMPLOT3D_SOURCE_DIR}/implot3d.cpp
    ${IMPLOT3D_SOURCE_DIR}/implot3d_demo.cpp
    ${IMPLOT3D_SOURCE_DIR}/implot3d_items.cpp
    ${IMPLOT3D_SOURCE_DIR}/implot3d_meshes.cpp
)
add_library(implot3d STATIC ${IMPLOT3D_SOURCE})
target_include_directories(implot3d PUBLIC ${IMPLOT3D_SOURCE_DIR})
target_link_libraries(implot3d PUBLIC imgui)

#PerlinNoise-Kernel
# This is bundled so we don't need to install it
if (PNV_PREFER_BUNDLED_THIRD_PARTIES)
  if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/PerlinNoise-Kernel/CMakeLists.txt)
    add_subdirectory (PerlinNoise-Kernel)
  else ()
    message (WARNING
      "\nBundled library PNK not found! Falling back to system version of PNK!"
      "\nYou may have cloned the repository without the --recursive flag."
      "\nUse `git submodule update --init --recursive` to download dependencies."
      "\nOr you can install this library by yourself :3"
    )
  endif ()
endif ()

