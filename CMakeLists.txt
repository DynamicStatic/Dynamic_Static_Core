
# CMake configuration for Dynamic_Static.Core

cmake_minimum_required(VERSION 3.2)
project(Dynamic_Static.Core)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(PACKAGE_DIRECTORY ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.Package/)
set(LIBRARY_OUTPUT_PATH ${PACKAGE_DIRECTORY}/lib/)

set(DYNAMIC_STATIC_CORE_EXTERNAL
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/external/
)

# include(ExternalProject)
# include(CheckIncludeFile)
# include(CheckIncludeFiles)
# include(CheckIncludeFileCXX)
# include(${DYNAMIC_STATIC_CORE_EXTERNAL}/glfw.cmake)

set(DYNAMIC_STATIC_CORE_INCLUDE
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include/
)

# set(GLFW_BUILD_TESTS false)
# set(GLFW_BUILD_EXAMPLES false)
add_subdirectory(${DYNAMIC_STATIC_CORE_EXTERNAL}/glfw-3.2.1/)
add_subdirectory(${PROJECT_NAME}/)
add_subdirectory(Sandbox/)
add_subdirectory(Tests/)

set(PLATFORM_BUILD_SCRIPTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PlatformBuildScripts/)

if (UNIX)
    add_custom_target(
        run ALL
        COMMAND /bin/sh ${PLATFORM_BUILD_SCRIPTS_DIR}/build.sh "${PACKAGE_DIRECTORY}"
        DEPENDS ${PROJECT_NAME}
        VERBATIM
    )
endif (UNIX)

if (WIN32)
    # build.bat

    # @ECHO OFF
    # set PATH="C:\\Some\\Path;%PATH%"
    # %*

    # add_custom_target(
    #     ...
    #     COMMAND cmd /c $CMAKE_CURRENT_SOURCE_DIR}/build.bat
    # )
endif (WIN32)
