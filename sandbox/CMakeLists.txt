
set(INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}/sandbox/include/")
set(INCLUDE_FILES
)

set(SOURCE_DIRECTORY "${PROJECT_SOURCE_DIR}/sandbox/source/")
set(SOURCE_FILES
    ${SOURCE_DIRECTORY}/Main.cpp
)

set(TARGET Dynamic_Static.Core.Sandbox)
add_executable(${TARGET} "${INCLUDE_FILES}" "${SOURCE_FILES}")
target_link_libraries(${TARGET} Dynamic_Static.Core)
dst_create_file_group("${INCLUDE_FILES}")
dst_create_file_group("${SOURCE_FILES}")
