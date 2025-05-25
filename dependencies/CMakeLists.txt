# here we add all dependencies

#glad
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/glad)

# GLFWPP
#set (GLFWPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # disable building examples
#add_subdirectory_checked (${CMAKE_CURRENT_SOURCE_DIR}/glfwpp)

#imgui
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/imgui)

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

