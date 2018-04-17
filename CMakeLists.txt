
#==========================================
#    Licensed under the MIT license
#    Copyright 2011-2018 Dynamic_Static
#       Patrick Purcell
#    http://opensource.org/licenses/MIT
#==========================================

# CMake configuration for Dynamic_Static.Core
cmake_minimum_required(VERSION 3.3)
include("external/Dynamic_Static.CMake/.cmake")

DstCreateProject(Dynamic_Static.Core)
include("external/glm.cmake")
include("external/GSL.cmake")
include("external/tclap.cmake")
set(includePath "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/")
set(sourcePath "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/Core/")
# DstCreateStaticLibrary(
#     target Dynamic_Static.Core
#     includeDirectories
#         "${CMAKE_CURRENT_LIST_DIR}/include/"
#         ${glm.includeDirectories}
#         ${gsl.includeDirectories}
#         ${tclap.includeDirectories}
# 
#     includeFiles
# 
#     sourceFiles
# )
