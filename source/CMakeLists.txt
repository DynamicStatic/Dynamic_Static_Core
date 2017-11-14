
# CMake configuration for Dynamic_Static.Core

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/Dynamic_Static/Core/)
set(INCLUDE_FILES
    ${INCLUDE_PATH}/Events.hpp
    ${INCLUDE_PATH}/Events/Delegate.hpp
    ${INCLUDE_PATH}/Events/Event.hpp
    ${INCLUDE_PATH}/Events/Subscribable.hpp

    ${INCLUDE_PATH}/FileSystem.hpp
    ${INCLUDE_PATH}/FileSystem/Directory.hpp
    ${INCLUDE_PATH}/FileSystem/File.hpp
    ${INCLUDE_PATH}/FileSystem/Path.hpp
    ${INCLUDE_PATH}/FileSystem/StdFileSystemInclude.hpp

    ${INCLUDE_PATH}/Math.hpp
    ${INCLUDE_PATH}/Math/Color.hpp
    ${INCLUDE_PATH}/Math/Defines.hpp
    ${INCLUDE_PATH}/Math/Matrix4x4.hpp
    ${INCLUDE_PATH}/Math/Quaternion.hpp
    ${INCLUDE_PATH}/Math/Rectangle.hpp
    ${INCLUDE_PATH}/Math/Transform.hpp
    ${INCLUDE_PATH}/Math/Utilities.hpp
    ${INCLUDE_PATH}/Math/Vector2.hpp
    ${INCLUDE_PATH}/Math/Vector3.hpp
    ${INCLUDE_PATH}/Math/Vector4.hpp

    ${INCLUDE_PATH}/Threads.hpp
    ${INCLUDE_PATH}/Threads/Semaphore.hpp
    ${INCLUDE_PATH}/Threads/ThreadPool.hpp
    ${INCLUDE_PATH}/Threads/ThreadUtilities.hpp
    ${INCLUDE_PATH}/Threads/Worker.hpp

    ${INCLUDE_PATH}/Action.hpp
    ${INCLUDE_PATH}/Algorithm.hpp
    ${INCLUDE_PATH}/BinaryReader.hpp
    ${INCLUDE_PATH}/Callback.hpp
    ${INCLUDE_PATH}/Defines.hpp
    ${INCLUDE_PATH}/Memory.hpp
    ${INCLUDE_PATH}/NonCopyable.hpp
    ${INCLUDE_PATH}/NonMoveable.hpp
    ${INCLUDE_PATH}/NotImplementedError.hpp
    ${INCLUDE_PATH}/Object.hpp
    ${INCLUDE_PATH}/Random.hpp
    ${INCLUDE_PATH}/SharedObjectFactory.hpp
    ${INCLUDE_PATH}/String.hpp
    ${INCLUDE_PATH}/StringUtilities.hpp
    ${INCLUDE_PATH}/Time.hpp
    ${INCLUDE_PATH}/ToString.hpp
    ${INCLUDE_PATH}/TupleUtilities.hpp
    ${INCLUDE_PATH}/TypeUtilities.hpp
    ${INCLUDE_PATH}/VectorUtilities.hpp
    ${INCLUDE_PATH}/Version.hpp
    ${INCLUDE_PATH}/Win32LeanAndMean.hpp
)

set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Dynamic_Static/Core/)
set(SOURCE_FILES
    ${SOURCE_PATH}/FileSystem/Directory.cpp
    ${SOURCE_PATH}/FileSystem/File.cpp
    ${SOURCE_PATH}/FileSystem/Path.cpp

    ${SOURCE_PATH}/Math/Color.cpp
    ${SOURCE_PATH}/Math/Matrix4x4.cpp
    ${SOURCE_PATH}/Math/Quaternion.cpp
    ${SOURCE_PATH}/Math/Vector2.cpp
    ${SOURCE_PATH}/Math/Vector3.cpp
    ${SOURCE_PATH}/Math/Vector4.cpp

    ${SOURCE_PATH}/Threads/Semaphore.cpp
    ${SOURCE_PATH}/Threads/ThreadPool.cpp
    ${SOURCE_PATH}/Threads/Worker.cpp

    ${SOURCE_PATH}/BinaryReader.cpp
    ${SOURCE_PATH}/Memory.cpp
    ${SOURCE_PATH}/NotImplementedError.cpp
    ${SOURCE_PATH}/Object.cpp
    ${SOURCE_PATH}/String.cpp
    ${SOURCE_PATH}/StringUtilities.cpp
    ${SOURCE_PATH}/Version.cpp
    ${SOURCE_PATH}/Win32LeanAndMean.cpp
)

if (MSVC)
    set(SYSTEM_INSTALL_DEPENDENCIES
    )
else()
    set(SYSTEM_INSTALL_DEPENDENCIES
        dl
        pthread
        stdc++fs
    )
endif()

set(TARGET Dynamic_Static.Core)
add_library(${TARGET} ${INCLUDE_FILES} ${SOURCE_FILES})
set_target_properties(${TARGET} PROPERTIES PREFIX "")

target_include_directories(
    ${TARGET}
    PUBLIC ${PROJECT_SOURCE_DIR}/include/
)

target_link_libraries(
    ${TARGET}
    PUBLIC ${SYSTEM_INSTALL_DEPENDENCIES}
)

create_file_group("${INCLUDE_FILES}")
create_file_group("${SOURCE_FILES}")

export(
    TARGETS ${TARGET}
    FILE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.package.cmake
)
