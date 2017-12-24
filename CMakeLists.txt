
# CMake configuration for Dynamic_Static.Core
cmake_minimum_required(VERSION 3.3)
################################################################################
set(Dynamic_Static.cmake "${CMAKE_BINARY_DIR}/Dynamic_Static.cmake")
file(
    DOWNLOAD
    https://raw.githubusercontent.com/DynamicStatic/Dynamic_Static.CMake/refactor/build-system/Dynamic_Static.cmake
    ${Dynamic_Static.cmake}
)

include(${Dynamic_Static.cmake})
################################################################################
dst_create_project(Dynamic_Static.Core)
include("${CMAKE_CURRENT_SOURCE_DIR}/external/glm.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/external/gsl.cmake")
set(includePath "${CMAKE_CURRENT_SOURCE_DIR}/include/Dynamic_Static/Core/")
set(sourcePath "${CMAKE_CURRENT_SOURCE_DIR}/source/Dynamic_Static/Core/")
dst_add_static_library(
    target Dynamic_Static.Core
    includeDirectories
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        ${glm.includeDirectories}
        ${gsl.includeDirectories}

    includeFiles
        ${includePath}/Events/Delegate.hpp
        ${includePath}/Events/Event.hpp
        ${includePath}/Events/Subscribable.hpp
        ${includePath}/FileSystem/Directory.hpp
        ${includePath}/FileSystem/File.hpp
        ${includePath}/FileSystem/Path.hpp
        ${includePath}/FileSystem/StdFileSystemInclude.hpp
        ${includePath}/Math/Colors.hpp
        ${includePath}/Math/Defines.hpp
        ${includePath}/Math/Transform.hpp
        ${includePath}/Math/Utilities.hpp
        ${includePath}/Threads/Semaphore.hpp
        ${includePath}/Threads/ThreadPool.hpp
        ${includePath}/Threads/ThreadUtilities.hpp
        ${includePath}/Threads/Worker.hpp
        ${includePath}/Action.hpp
        ${includePath}/Algorithm.hpp
        ${includePath}/BinaryReader.hpp
        ${includePath}/Callback.hpp
        ${includePath}/Defines.hpp
        ${includePath}/Events.hpp
        ${includePath}/FileSystem.hpp
        ${includePath}/Math.hpp
        ${includePath}/Memory.hpp
        ${includePath}/NonCopyable.hpp
        ${includePath}/NonMoveable.hpp
        ${includePath}/NotImplementedError.hpp
        ${includePath}/Object.hpp
        ${includePath}/Random.hpp
        ${includePath}/SharedObjectFactory.hpp
        ${includePath}/String.hpp
        ${includePath}/StringUtilities.hpp
        ${includePath}/Threads.hpp
        ${includePath}/Time.hpp
        ${includePath}/ToString.hpp
        ${includePath}/TupleUtilities.hpp
        ${includePath}/TypeUtilities.hpp
        ${includePath}/VectorUtilities.hpp
        ${includePath}/Version.hpp
        ${includePath}/Win32LeanAndMean.hpp

    sourceFiles
        ${sourcePath}/FileSystem/Directory.cpp
        ${sourcePath}/FileSystem/File.cpp
        ${sourcePath}/FileSystem/Path.cpp
        ${sourcePath}/Threads/Semaphore.cpp
        ${sourcePath}/Threads/ThreadPool.cpp
        ${sourcePath}/Threads/Worker.cpp
        ${sourcePath}/BinaryReader.cpp
        ${sourcePath}/Colors.cpp
        ${sourcePath}/Memory.cpp
        ${sourcePath}/NotImplementedError.cpp
        ${sourcePath}/Object.cpp
        ${sourcePath}/String.cpp
        ${sourcePath}/StringUtilities.cpp
        ${sourcePath}/Version.cpp
        ${sourcePath}/Win32LeanAndMean.cpp
)

option(BUILD_TESTS "Build Dynamic_Static.Core tests" ON)
if (BUILD_TESTS)
    set(testsPath "${CMAKE_CURRENT_SOURCE_DIR}/tests/")
    dst_add_tests(
        target Dynamic_Static.Core
        sourceFiles
            ${testsPath}/Events/Events.Tests.cpp
            ${testsPath}/Events/Events.Tests.inl
            ${testsPath}/FileSystem/File.Tests.cpp
            ${testsPath}/FileSystem/Path.Tests.cpp
            ${testsPath}/Threads/Semaphore.Tests.cpp
            ${testsPath}/Threads/ThreadPool.Tests.cpp
            ${testsPath}/Threads/Worker.Tests.cpp
            ${testsPath}/Algorithm.Tests.cpp
            ${testsPath}/BinaryReader.Tests.cpp
            ${testsPath}/Callback.Tests.cpp
            ${testsPath}/LoremIpsum.hpp
            ${testsPath}/LoremIpsum.txt
            ${testsPath}/Random.Tests.cpp
            ${testsPath}/StringUtilities.Tests.cpp
            ${testsPath}/ToString.Tests.cpp
            ${testsPath}/VectorUtilities.Tests.cpp
    )

    file(COPY "${testsPath}/LoremIpsum.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
endif()
