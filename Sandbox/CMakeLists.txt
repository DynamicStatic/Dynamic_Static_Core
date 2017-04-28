
# CMake configuration for Dynamic_Static.Core/Sandbox

include_directories(
    include/
    ${DYNAMIC_STATIC_CORE_INCLUDE}
)

add_executable(
    Dynamic_Static.Core.Sandbox
    ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
)

target_link_libraries(
    Dynamic_Static.Core.Sandbox
    Dynamic_Static.Core
    pthread
)
