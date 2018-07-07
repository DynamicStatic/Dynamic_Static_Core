
#==========================================
#  Copyright (c) 2016-2018 Dynamic_Static
#    Patrick Purcell
#      Licensed under the MIT license
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
        ${includePath}/Events/Delegate.hpp
        ${includePath}/Events/Event.hpp
        ${includePath}/Events/Subscribable.hpp
        ${includePath}/Math/Colors.hpp
        ${includePath}/Math/Defines.hpp
        ${includePath}/Math/Transform.hpp
        ${includePath}/Math/Utilities.hpp
        ${includePath}/Threads/Semaphore.hpp
        ${includePath}/Threads/ThreadPool.hpp
        ${includePath}/Threads/ThreadUtilities.hpp
        ${includePath}/Threads/Worker.hpp
        ${includePath}/Algorithm.hpp
        ${includePath}/Callback.hpp
        ${includePath}/Defines.hpp
        ${includePath}/Events.hpp
        ${includePath}/File.hpp
        ${includePath}/Math.hpp
        ${includePath}/Memory.hpp
        ${includePath}/NonCopyable.hpp
        ${includePath}/Random.hpp
        ${includePath}/StdFileSystemInclude.hpp
        ${includePath}/StringUtilities.hpp
        ${includePath}/Threads.hpp
        ${includePath}/Time.hpp
        ${includePath}/VectorUtilities.hpp
        ${includePath}/Win32LeanAndMean.hpp

    sourceFiles
        ${CMAKE_CURRENT_LIST_DIR}/ForceCMakeBuild.cpp
)

option(BUILD_TESTS "Build Dynamic_Static.Core.Tests" ON)
if(BUILD_TESTS)
    set(testsPath "${CMAKE_CURRENT_LIST_DIR}/tests.ex/")
    DstCreateTests(
        target Dynamic_Static.Core
        folder Dynamic_Static.Core/
        sourceFiles
            ${testsPath}/Events/Events.Tests.cpp
            ${testsPath}/Events/Events.Tests.inl
            ${testsPath}/Threads/Semaphore.Tests.cpp
            ${testsPath}/Threads/ThreadPool.Tests.cpp
            ${testsPath}/Threads/Worker.Tests.cpp
            ${testsPath}/Random.Tests.cpp
            ${testsPath}/StringUtilities.Tests.cpp
            ${testsPath}/VectorUtilities.Tests.cpp
    )
endif()
