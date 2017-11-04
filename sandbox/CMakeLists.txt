
# CMake configuration for Dynamic_Static.Core.Sandbox

set(INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(INCLUDE_FILES
)

set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/)
set(SOURCE_FILES
    ${SOURCE_DIRECTORY}/Main.cpp
)

set(TARGET Dynamic_Static.Core.Sandbox)
add_executable(${TARGET} ${INCLUDE_FILES} ${SOURCE_FILES})

target_link_libraries(
    ${TARGET}
    Dynamic_Static.Core
)

create_file_group("${INCLUDE_FILES}")
create_file_group("${SOURCE_FILES}")
