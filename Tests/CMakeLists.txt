
# CMake configuration for Dynamic_Static_Core/Tests

include_directories(
    include/
    ${DYNAMIC_STATIC_CORE_INCLUDE}
)

add_executable(
    Dynamic_Static_Core.Tests
    ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/BinaryReader.Tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Event.Tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/MoveableHandle.Tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/MoveNotifier.Tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Random.Tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/StringUtilities.Tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Threads.Tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/VectorUtilities.Tests.cpp
)

target_link_libraries(
    Dynamic_Static_Core.Tests
    Dynamic_Static_Core
    pthread
)
