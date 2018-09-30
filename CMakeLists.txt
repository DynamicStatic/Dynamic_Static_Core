
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

set(includeDirectory "${CMAKE_CURRENT_LIST_DIR}/include/")
set(includePath "${includeDirectory}/Dynamic_Static/Core/")
DstCreateStaticLibrary(
    target Dynamic_Static.Core
    folder Dynamic_Static.Core/

    includeDirectories
        "${includeDirectory}"
        "${glm.includeDirectories}"

    includeFiles
        "${includePath}/Events/Delegate.hpp"
        "${includePath}/Events/Event.hpp"
        "${includePath}/Events/Subscribable.hpp"
        "${includePath}/Math/Colors.hpp"
        "${includePath}/Math/Defines.hpp"
        "${includePath}/Math/Transform.hpp"
        "${includePath}/Math/Utilities.hpp"
        "${includePath}/Threads/Semaphore.hpp"
        "${includePath}/Threads/ThreadPool.hpp"
        "${includePath}/Threads/ThreadUtilities.hpp"
        "${includePath}/Threads/Worker.hpp"
        "${includePath}/Action.hpp"
        "${includePath}/Algorithm.hpp"
        "${includePath}/Callback.hpp"
        "${includePath}/Component.hpp"
        "${includePath}/Defines.hpp"
        "${includePath}/Entity.hpp"
        "${includePath}/Events.hpp"
        "${includePath}/File.hpp"
        "${includePath}/FileSystem.hpp"
        "${includePath}/Math.hpp"
        "${includePath}/Memory.hpp"
        "${includePath}/MoveNotifier.hpp"
        "${includePath}/NonCopyable.hpp"
        "${includePath}/Random.hpp"
        "${includePath}/SharedObject.hpp"
        "${includePath}/Span.hpp"
        "${includePath}/StringUtilities.hpp"
        "${includePath}/StringView.hpp"
        "${includePath}/Threads.hpp"
        "${includePath}/Time.hpp"
        "${includePath}/TypeUtilities.hpp"
        "${includePath}/VectorUtilities.hpp"
        "${includePath}/Version.hpp"
        "${includePath}/Win32LeanAndMean.hpp"

    sourceFiles
        "${CMAKE_CURRENT_LIST_DIR}/ForceCMakeBuild.cpp"
)

option(BUILD_DST_TESTS "Build Dynamic_Static.Core.Tests" ON)
if(BUILD_DST_TESTS)
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
            "${testsPath}/StringView.Tests.cpp"
            "${testsPath}/VectorUtilities.Tests.cpp"
    )
endif()

option(BUILD_DST_HEADER_GENERATOR "Build Dynamic_Static.Core.HeaderGenerator" ON)
if(BUILD_DST_HEADER_GENERATOR)
    DstCreateExecutable(
        target Dynamic_Static.Core.HeaderGenerator
        folder Dynamic_Static.Core/
        includeDirectories "${CMAKE_CURRENT_LIST_DIR}/include/"
        sourceFiles "${CMAKE_CURRENT_LIST_DIR}/HeaderGenerator.Main.cpp"
    )
    target_compile_definitions(
        Dynamic_Static.Core.HeaderGenerator
        PRIVATE
            DYNAMIC_STATIC_CORE_INCLUDE_DIRECTORY="${CMAKE_CURRENT_LIST_DIR}/include/"
    )
endif()
