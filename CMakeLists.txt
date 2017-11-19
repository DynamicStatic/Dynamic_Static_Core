
# CMake configuration for Dynamic_Static.Core
cmake_minimum_required(VERSION 3.3)

set(Dynamic_Static.cmake "${CMAKE_BINARY_DIR}/Dynamic_Static.cmake")
file(
    DOWNLOAD
    https://raw.githubusercontent.com/DynamicStatic/Dynamic_Static.CMake/master/Dynamic_Static.cmake
    ${Dynamic_Static.cmake}
)

include(${Dynamic_Static.cmake})
dst_create_project(Dynamic_Static.Core)
set(CMAKE_CXX_STANDARD 14)
add_subdirectory("source/")

option(BUILD_SANDBOX "Build Dynamic_Static.Core sandbox" ON)
if (BUILD_SANDBOX)
    add_subdirectory("sandbox/")
endif()

option(BUILD_TESTS "Build Dynamic_Static.Core tests" ON)
if (BUILD_TESTS)
    add_subdirectory("tests/")
endif()
