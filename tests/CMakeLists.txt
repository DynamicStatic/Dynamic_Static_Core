
# CMake configuration for Dynamic_Static.Core.Tests

set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/)
set(SOURCE_PATH ${SOURCE_DIRECTORY}Dynamic_Static/Core/)
set(SOURCE_FILES
    ${SOURCE_DIRECTORY}/Main.cpp
    ${SOURCE_PATH}/Events/Events.Tests.cpp
    ${SOURCE_PATH}/Events/Events.Tests.inl

    ${SOURCE_PATH}/FileSystem/Path.Tests.cpp

    ${SOURCE_PATH}/Math/Matrix4x4.Tests.cpp
    ${SOURCE_PATH}/Math/Quaternion.Tests.cpp
    ${SOURCE_PATH}/Math/Vector.Tests.inl
    ${SOURCE_PATH}/Math/Vector2.Tests.cpp
    ${SOURCE_PATH}/Math/Vector3.Tests.cpp
    ${SOURCE_PATH}/Math/Vector4.Tests.cpp

    ${SOURCE_PATH}/Threads/Semaphore.Tests.cpp
    ${SOURCE_PATH}/Threads/ThreadPool.Tests.cpp
    ${SOURCE_PATH}/Threads/Worker.Tests.cpp

    ${SOURCE_PATH}/Algorithm.Tests.cpp
    ${SOURCE_PATH}/Random.Tests.cpp
    ${SOURCE_PATH}/StringUtilities.Tests.cpp
    ${SOURCE_PATH}/ToString.Tests.cpp
    ${SOURCE_PATH}/VectorUtilities.Tests.cpp
)

create_file_group("${INCLUDE_FILES}")
create_file_group("${SOURCE_FILES}")

set(TARGET Dynamic_Static.Core.Tests)
add_executable(${TARGET} ${SOURCE_FILES})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TARGET} Dynamic_Static.Core)
add_dependencies(${TARGET} Dynamic_Static.Core)
