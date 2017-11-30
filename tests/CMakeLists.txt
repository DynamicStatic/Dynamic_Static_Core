
set(sourcePath "${PROJECT_SOURCE_DIR}/tests/source/")
set(sourceFiles
    ${sourcePath}/Events/Events.Tests.cpp
    ${sourcePath}/Events/Events.Tests.inl

    ${sourcePath}/FileSystem/File.Tests.cpp
    ${sourcePath}/FileSystem/Path.Tests.cpp

    ${sourcePath}/Threads/Semaphore.Tests.cpp
    ${sourcePath}/Threads/ThreadPool.Tests.cpp
    ${sourcePath}/Threads/Worker.Tests.cpp

    ${sourcePath}/Algorithm.Tests.cpp
    ${sourcePath}/BinaryReader.Tests.cpp
    ${sourcePath}/Callback.Tests.cpp
    ${sourcePath}/LoremIpsum.hpp
    ${sourcePath}/LoremIpsum.txt
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

set(target Dynamic_Static.Core.Tests)
add_executable(${target} "${sourceFiles}")
add_dependencies(${target} Dynamic_Static.Core)
dst_setup_target(${target} "" "${sourceFiles}")
target_include_directories(${target} PUBLIC ${catch.include})
target_link_libraries(${target} PUBLIC Dynamic_Static.Core)
file(COPY "${sourcePath}/LoremIpsum.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
