
file(
    DOWNLOAD
    https://github.com/Microsoft/GSL/archive/master.zip
    "${CMAKE_BINARY_DIR}/external/downloads/GSL-master.zip"
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf "${CMAKE_BINARY_DIR}/external/downloads/GSL-master.zip"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/external/"
)

set(gsl.includeDirectories "${CMAKE_BINARY_DIR}/external/GSL-master/include/")
