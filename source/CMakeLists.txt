
include("${PROJECT_SOURCE_DIR}/external/glm.cmake")
include("${PROJECT_SOURCE_DIR}/external/gsl.cmake")

set(includePath "${PROJECT_SOURCE_DIR}/include/Dynamic_Static/Core/")
set(includeFiles
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
)

set(sourcePath "${PROJECT_SOURCE_DIR}/source/Dynamic_Static/Core/")
set(sourceFiles
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

add_library(${CMAKE_PROJECT_NAME} STATIC "${includeFiles}" "${sourceFiles}")
add_dependencies(${CMAKE_PROJECT_NAME} glm)
add_dependencies(${CMAKE_PROJECT_NAME} gsl)
dst_setup_target(${CMAKE_PROJECT_NAME} "${includeFiles}" "${sourceFiles}")

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC ${glm.include}
    PUBLIC ${gsl.include}
)

dst_export_target(${CMAKE_PROJECT_NAME})
