
#==========================================
#    Copyright 2011-2018 Dynamic_Static
#        Patrick Purcell
#    Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

# CMake configuration for Dynamic_Static.Core
cmake_minimum_required(VERSION 3.3)
option(SDK_BUILD "TODO : This shouldn't be the default" ON)
if(SDK_BUILD)
    include("$ENV{DYNAMIC_STATIC_SDK}/Dynamic_Static.CMake/.cmake")
else()
    include("external/Dynamic_Static.CMake/.cmake")
endif()
DstCreateProject(Dynamic_Static.Core)

include("external/glm.cmake")
include("external/GSL.cmake")
include("external/tclap.cmake")

set(includePath "${CMAKE_CURRENT_LIST_DIR}/include.ex/Dynamic_Static/Core/")
set(sourcePath "${CMAKE_CURRENT_LIST_DIR}/source.ex/Dynamic_Static/Core/")
DstCreateStaticLibrary(
    target Dynamic_Static.Core
    folder Dynamic_Static.Core/
    includeDirectories
        "${CMAKE_CURRENT_LIST_DIR}/include.ex/"
        ${glm.includeDirectories}
        ${GSL.includeDirectories}
        ${tclap.includeDirectories}

    includeFiles
        ${includePath}/Math/Colors.hpp
        ${includePath}/Math/Defines.hpp
        ${includePath}/Callback.hpp
        ${includePath}/Defines.hpp
        ${includePath}/Math.hpp
        ${includePath}/NonCopyable.hpp
        ${includePath}/StringUtilities.hpp
        ${includePath}/Version.hpp
        ${includePath}/Win32LeanAndMean.hpp

    sourceFiles
        ${sourcePath}/Colors.cpp
)

option(BUILD_TESTS "Build Dynamic_Static.Core.Tests" ON)
if(BUILD_TESTS)
    set(testsPath "${CMAKE_CURRENT_LIST_DIR}/tests.ex/")
    DstCreateTests(
        target Dynamic_Static.Core
        folder Dynamic_Static.Core/
        sourceFiles
            ${testsPath}/BinaryWriter.Tests.cpp
            ${testsPath}/BinaryReader.Tests.cpp
            ${testsPath}/StringUtilities.Tests.cpp
    )
endif()
