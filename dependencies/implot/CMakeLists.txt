cmake_minimum_required (VERSION 3.19)
project (${PROJECT_NAME} LANGUAGES CXX)

# implot
add_library (implot
    implot/implot.cpp
    implot/implot_demo.cpp
    implot/implot.h
    implot/implot_internal.h
    implot/implot_items.cpp
)

target_include_directories(implot PUBLIC
    implot
)
target_link_libraries(implot PUBLIC imgui)

if (WIN32 AND NOT (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC"))
    target_link_libraries(implot PUBLIC "Imm32.lib")
endif()