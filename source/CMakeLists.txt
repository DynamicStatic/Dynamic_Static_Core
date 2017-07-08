
# CMake configuration for Dynamic_Static.Core/source

set(INCLUDE_PATH ${DST_CORE_INCLUDE}/Dynamic_Static/)
set(INCLUDE_FILES
    ${INCLUDE_PATH}/Core/Events.hpp
    ${INCLUDE_PATH}/Core/Events/Delegate.hpp
    ${INCLUDE_PATH}/Core/Events/Event.hpp
    ${INCLUDE_PATH}/Core/Events/Subscribable.hpp

    ${INCLUDE_PATH}/Core/FileSystem.hpp
    ${INCLUDE_PATH}/Core/FileSystem/Directory.hpp
    ${INCLUDE_PATH}/Core/FileSystem/File.hpp
    ${INCLUDE_PATH}/Core/FileSystem/Path.hpp
    ${INCLUDE_PATH}/Core/FileSystem/StdFileSystemInclude.hpp

    ${INCLUDE_PATH}/Core/Math.hpp
    ${INCLUDE_PATH}/Core/Math/Color.hpp
    ${INCLUDE_PATH}/Core/Math/Defines.hpp
    ${INCLUDE_PATH}/Core/Math/Matrix4x4.hpp
    ${INCLUDE_PATH}/Core/Math/Quaternion.hpp
    ${INCLUDE_PATH}/Core/Math/Rectangle.hpp
    ${INCLUDE_PATH}/Core/Math/Transform.hpp
    ${INCLUDE_PATH}/Core/Math/Utilities.hpp
    ${INCLUDE_PATH}/Core/Math/Vector2.hpp
    ${INCLUDE_PATH}/Core/Math/Vector3.hpp
    ${INCLUDE_PATH}/Core/Math/Vector4.hpp

    ${INCLUDE_PATH}/Core/Threads.hpp
    ${INCLUDE_PATH}/Core/Threads/Semaphore.hpp
    ${INCLUDE_PATH}/Core/Threads/ThreadPool.hpp
    ${INCLUDE_PATH}/Core/Threads/ThreadUtilities.hpp
    ${INCLUDE_PATH}/Core/Threads/Worker.hpp

    ${INCLUDE_PATH}/Core/Action.hpp
    ${INCLUDE_PATH}/Core/Algorithm.hpp
    ${INCLUDE_PATH}/Core/BinaryReader.hpp
    ${INCLUDE_PATH}/Core/Callback.hpp
    ${INCLUDE_PATH}/Core/Collection.hpp
    ${INCLUDE_PATH}/Core/Defines.hpp
    ${INCLUDE_PATH}/Core/NonCopyable.hpp
    ${INCLUDE_PATH}/Core/NonMoveable.hpp
    ${INCLUDE_PATH}/Core/NotImplementedError.hpp
    ${INCLUDE_PATH}/Core/Object.hpp
    ${INCLUDE_PATH}/Core/Random.hpp
    ${INCLUDE_PATH}/Core/SharedObjectFactory.hpp
    ${INCLUDE_PATH}/Core/String.hpp
    ${INCLUDE_PATH}/Core/StringUtilities.hpp
    ${INCLUDE_PATH}/Core/Time.hpp
    ${INCLUDE_PATH}/Core/ToString.hpp
    ${INCLUDE_PATH}/Core/TypeUtilities.hpp
    ${INCLUDE_PATH}/Core/VectorUtilities.hpp
    ${INCLUDE_PATH}/Core/Version.hpp
    ${INCLUDE_PATH}/Core/Win32LeanAndMean.hpp
)

set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Dynamic_Static/Core/)
set(SOURCE_FILES
    ${SOURCE_PATH}/FileSystem/Directory.cpp
    ${SOURCE_PATH}/FileSystem/File.cpp
    ${SOURCE_PATH}/FileSystem/Path.cpp
    
    ${SOURCE_PATH}/Threads/Semaphore.cpp
    ${SOURCE_PATH}/Threads/ThreadPool.cpp
    ${SOURCE_PATH}/Threads/Worker.cpp
    
    ${SOURCE_PATH}/BinaryReader.cpp
    ${SOURCE_PATH}/NotImplementedError.cpp
    ${SOURCE_PATH}/Object.cpp
    ${SOURCE_PATH}/String.cpp
    ${SOURCE_PATH}/StringUtilities.cpp
    ${SOURCE_PATH}/Version.cpp
    ${SOURCE_PATH}/Win32LeanAndMean.cpp
)

if (MSVC)
    set(DST_CORE_DEPENDENCIES
        PARENT_SCOPE
    )
else()
    set(DST_CORE_DEPENDENCIES
        stdc++fs
        pthread
        PARENT_SCOPE
    )
endif()

add_library(Dynamic_Static.Core ${INCLUDE_FILES} ${SOURCE_FILES})
set_target_properties(Dynamic_Static.Core PROPERTIES PREFIX "")
create_file_group("${INCLUDE_FILES}")
create_file_group("${SOURCE_FILES}")
