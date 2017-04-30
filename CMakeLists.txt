
# CMake configuration for Dynamic_Static.Core

cmake_minimum_required (VERSION 3.2)
project(Dynamic_Static.Core)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(PACKAGE_DIRECTORY ${PROJECT_BINARY_DIR}/Dynamic_Static.Core.Package/)
set(LIBRARY_OUTPUT_PATH ${PACKAGE_DIRECTORY}/lib/)

set(DYNAMIC_STATIC_CORE_EXTERNAL
    ${CMAKE_SOURCE_DIR}/Dynamic_Static.Core/external/
)

# include(ExternalProject)
# include(CheckIncludeFile)
# include(CheckIncludeFiles)
# include(CheckIncludeFileCXX)
# include(${DYNAMIC_STATIC_CORE_EXTERNAL}/glfw.cmake)

set(DYNAMIC_STATIC_CORE_INCLUDE
    ${CMAKE_SOURCE_DIR}/Dynamic_Static.Core/include/
)

add_subdirectory(${DYNAMIC_STATIC_CORE_EXTERNAL}/glfw-3.2.1/)
add_subdirectory(Dynamic_Static.Core/)
add_subdirectory(Sandbox/)
add_subdirectory(Tests/)
