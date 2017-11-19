
set(includePath "${PROJECT_SOURCE_DIR}/sandbox/include/")
set(includeFiles
)

set(sourcePath "${PROJECT_SOURCE_DIR}/sandbox/source/")
set(sourceFiles
    ${sourcePath}/Main.cpp
)

set(TARGET Dynamic_Static.Core.Sandbox)
add_executable(${TARGET} "${includeFiles}" "${sourceFiles}")
add_dependencies(${TARGET} Dynamic_Static.Core)
dst_setup_target(${TARGET} "${includeFiles}" "${sourceFiles}")
target_link_libraries(${TARGET} Dynamic_Static.Core)
