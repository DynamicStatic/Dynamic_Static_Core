
# CMake configuration for Dynamic_Static.Core/Application

set(INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(INCLUDE_FILES
)

set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/)
set(SOURCE_FILES
    ${SOURCE_DIRECTORY}/Main.cpp
)

include_directories(
    ${INCLUDE_DIRECTORY}
    ${DYNAMIC_STATIC_CORE_INCLUDE_DIRECTORY}
)

add_executable(
    Dynamic_Static.Core.Application
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
)

target_link_libraries(
    Dynamic_Static.Core.Application
    Dynamic_Static.Core
    ${DYNAMIC_STATIC_CORE_DEPENDENCIES}
)

create_file_group("${INCLUDE_FILES}")
create_file_group("${SOURCE_FILES}")
