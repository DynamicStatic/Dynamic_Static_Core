
#==========================================
#  Copyright (c) 2016-2018 Dynamic_Static
#    Patrick Purcell
#      Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

# CMake configuration for Dynamic_Static.Core

cmake_minimum_required(VERSION 3.3)
if(DEFINED ENV{DYNAMIC_STATIC_SDK})
    include("$ENV{DYNAMIC_STATIC_SDK}/Dynamic_Static.CMake/.cmake")
else()
    include("external/Dynamic_Static.CMake/.cmake")
endif()

DstCreateProject(Dynamic_Static.Core)

include("external/glm.cmake")

set(includeDirectory "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/")
DstCreateStaticLibrary(
    target Dynamic_Static.Core
    folder Dynamic_Static.Core/

    includeDirectories
        "${CMAKE_CURRENT_LIST_DIR}/include/"
        ${glm.includeDirectories}

    includeFiles
        "${includeDirectory}/Events/Delegate.hpp"
        "${includeDirectory}/Events/Event.hpp"
        "${includeDirectory}/Events/Subscribable.hpp"
        "${includeDirectory}/Math/Colors.hpp"
        "${includeDirectory}/Math/Defines.hpp"
        "${includeDirectory}/Math/Transform.hpp"
        "${includeDirectory}/Math/Utilities.hpp"
        "${includeDirectory}/Threads/Semaphore.hpp"
        "${includeDirectory}/Threads/ThreadPool.hpp"
        "${includeDirectory}/Threads/ThreadUtilities.hpp"
        "${includeDirectory}/Threads/Worker.hpp"
        "${includeDirectory}/Action.hpp"
        "${includeDirectory}/Algorithm.hpp"
        "${includeDirectory}/Callback.hpp"
        "${includeDirectory}/Defines.hpp"
        "${includeDirectory}/Events.hpp"
        "${includeDirectory}/File.hpp"
        "${includeDirectory}/FileSystem.hpp"
        "${includeDirectory}/Math.hpp"
        "${includeDirectory}/Memory.hpp"
        "${includeDirectory}/MoveNotifier.hpp"
        "${includeDirectory}/NonCopyable.hpp"
        "${includeDirectory}/Random.hpp"
        "${includeDirectory}/SharedObject.hpp"
        "${includeDirectory}/Span.hpp"
        "${includeDirectory}/StringUtilities.hpp"
        "${includeDirectory}/StringView.hpp"
        "${includeDirectory}/Threads.hpp"
        "${includeDirectory}/Time.hpp"
        "${includeDirectory}/VectorUtilities.hpp"
        "${includeDirectory}/Version.hpp"
        "${includeDirectory}/Win32LeanAndMean.hpp"

    sourceFiles
        "${CMAKE_CURRENT_LIST_DIR}/ForceCMakeBuild.cpp"
)

option(BUILD_TESTS "Build Dynamic_Static.Core.Tests" ON)
if(BUILD_TESTS)
    set(testsPath "${CMAKE_CURRENT_LIST_DIR}/tests/")
    DstCreateTests(
        target Dynamic_Static.Core
        folder Dynamic_Static.Core/

        sourceFiles
            "${testsPath}/Events/Delegate.Tests.cpp"
            "${testsPath}/Events/Event.Tests.cpp"
            "${testsPath}/Events/Subscribable.Tests.cpp"
            "${testsPath}/Threads/Semaphore.Tests.cpp"
            "${testsPath}/Threads/ThreadPool.Tests.cpp"
            "${testsPath}/Threads/Worker.Tests.cpp"
            "${testsPath}/Random.Tests.cpp"
            "${testsPath}/StringUtilities.Tests.cpp"
            "${testsPath}/VectorUtilities.Tests.cpp"
    )
endif()

option(BUILD_TESTS "Build Dynamic_Static.Core.HeaderGenerator" ON)
if(BUILD_TESTS)
    DstCreateExecutable(
        target Dynamic_Static.Core.HeaderGenerator
        folder Dynamic_Static.Core/
        includeDirectories
            "${CMAKE_CURRENT_LIST_DIR}/include/"

        sourceFiles
            "${CMAKE_CURRENT_LIST_DIR}/HeaderGenerator.Main.cpp"
    )
    target_compile_definitions(
        Dynamic_Static.Core.HeaderGenerator
        PRIVATE
            DYNAMIC_STATIC_CORE_INCLUDE_DIRECTORY="${CMAKE_CURRENT_LIST_DIR}/include/"
    )
endif()
