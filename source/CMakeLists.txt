
set(includePath "${PROJECT_SOURCE_DIR}/include/Dynamic_Static/Core/")
set(includeFiles
    ${includePath}/Events.hpp
    ${includePath}/Events/Delegate.hpp
    ${includePath}/Events/Event.hpp
    ${includePath}/Events/Subscribable.hpp

    ${includePath}/FileSystem.hpp
    ${includePath}/FileSystem/Directory.hpp
    ${includePath}/FileSystem/File.hpp
    ${includePath}/FileSystem/Path.hpp
    ${includePath}/FileSystem/StdFileSystemInclude.hpp

    ${includePath}/Math.hpp
    ${includePath}/Math/Color.hpp
    ${includePath}/Math/Defines.hpp
    ${includePath}/Math/Matrix4x4.hpp
    ${includePath}/Math/Quaternion.hpp
    ${includePath}/Math/Rectangle.hpp
    ${includePath}/Math/Transform.hpp
    ${includePath}/Math/Utilities.hpp
    ${includePath}/Math/Vector2.hpp
    ${includePath}/Math/Vector3.hpp
    ${includePath}/Math/Vector4.hpp

    ${includePath}/Threads.hpp
    ${includePath}/Threads/Semaphore.hpp
    ${includePath}/Threads/ThreadPool.hpp
    ${includePath}/Threads/ThreadUtilities.hpp
    ${includePath}/Threads/Worker.hpp

    ${includePath}/Action.hpp
    ${includePath}/Algorithm.hpp
    ${includePath}/BinaryReader.hpp
    ${includePath}/Callback.hpp
    ${includePath}/Defines.hpp
    ${includePath}/Memory.hpp
    ${includePath}/NonCopyable.hpp
    ${includePath}/NonMoveable.hpp
    ${includePath}/NotImplementedError.hpp
    ${includePath}/Object.hpp
    ${includePath}/Random.hpp
    ${includePath}/SharedObjectFactory.hpp
    ${includePath}/String.hpp
    ${includePath}/StringUtilities.hpp
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

    ${sourcePath}/Math/Color.cpp
    ${sourcePath}/Math/Matrix4x4.cpp
    ${sourcePath}/Math/Quaternion.cpp
    ${sourcePath}/Math/Vector2.cpp
    ${sourcePath}/Math/Vector3.cpp
    ${sourcePath}/Math/Vector4.cpp

    ${sourcePath}/Threads/Semaphore.cpp
    ${sourcePath}/Threads/ThreadPool.cpp
    ${sourcePath}/Threads/Worker.cpp

    ${sourcePath}/BinaryReader.cpp
    ${sourcePath}/Memory.cpp
    ${sourcePath}/NotImplementedError.cpp
    ${sourcePath}/Object.cpp
    ${sourcePath}/String.cpp
    ${sourcePath}/StringUtilities.cpp
    ${sourcePath}/Version.cpp
    ${sourcePath}/Win32LeanAndMean.cpp
)

dst_create_static_library("${includeFiles}" "${sourceFiles}")

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC ${glm.include}
    PUBLIC ${gsl.include}
)

if (EXISTS glm AND
    EXISTS gsl)
    add_dependencies(${CMAKE_PROJECT_NAME} glm)
    add_dependencies(${CMAKE_PROJECT_NAME} gsl)
endif()
