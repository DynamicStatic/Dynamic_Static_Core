
set(sourcePath "${PROJECT_SOURCE_DIR}/tests/source/")
set(sourceFiles
    ${sourcePath}/Events/Events.Tests.cpp
    ${sourcePath}/Events/Events.Tests.inl

    ${sourcePath}/FileSystem/Path.Tests.cpp

    ${sourcePath}/Math/Matrix4x4.Tests.cpp
    ${sourcePath}/Math/Quaternion.Tests.cpp
    ${sourcePath}/Math/Vector.Tests.inl
    ${sourcePath}/Math/Vector2.Tests.cpp
    ${sourcePath}/Math/Vector3.Tests.cpp
    ${sourcePath}/Math/Vector4.Tests.cpp

    ${sourcePath}/Threads/Semaphore.Tests.cpp
    ${sourcePath}/Threads/ThreadPool.Tests.cpp
    ${sourcePath}/Threads/Worker.Tests.cpp

    ${sourcePath}/Algorithm.Tests.cpp
    ${sourcePath}/Main.cpp
    ${sourcePath}/Random.Tests.cpp
    ${sourcePath}/StringUtilities.Tests.cpp
    ${sourcePath}/ToString.Tests.cpp
    ${sourcePath}/VectorUtilities.Tests.cpp
)

set(catch.include "${CMAKE_BINARY_DIR}/tests/external/catch/")
file(
    DOWNLOAD
    https://github.com/catchorg/Catch2/releases/download/v2.0.1/catch.hpp
    ${catch.include}/catch.hpp
)

set(TARGET Dynamic_Static.Core.Tests)
add_executable(${TARGET} "${sourceFiles}")
add_dependencies(${TARGET} Dynamic_Static.Core)
dst_setup_target(${TARGET} "" "${sourceFiles}")
target_include_directories(${TARGET} PUBLIC ${catch.include})
target_link_libraries(${TARGET} Dynamic_Static.Core)
