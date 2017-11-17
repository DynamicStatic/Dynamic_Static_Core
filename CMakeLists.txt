
# CMake configuration for Dynamic_Static.Core
cmake_minimum_required(VERSION 3.3)
cmake_policy(SET CMP0060 NEW)
include("${PROJECT_SOURCE_DIR}/Dynamic_Static.cmake")
dst_create_project(Dynamic_Static.Core)
add_subdirectory("source/")

# option(BUILD_SANDBOX "Build Dynamic_Static.Core sandbox" ON)
# if (BUILD_SANDBOX)
#     add_subdirectory("sandbox/")
# endif()
# 
# option(BUILD_TESTS "Build Dynamic_Static.Core tests" ON)
# if (BUILD_TESTS)
#     add_subdirectory("tests/")
# endif()
