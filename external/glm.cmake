
file(
    DOWNLOAD
    https://github.com/g-truc/glm/archive/master.zip
    # https://github.com/g-truc/glm/releases/download/0.9.8.5/glm-0.9.8.5.zip
    "${CMAKE_BINARY_DIR}/external/downloads/glm-master.zip"
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf "${CMAKE_BINARY_DIR}/external/downloads/glm-master.zip"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/external/"
)

file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/external/glm-master/cmake")
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/external/glm-master/doc")
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/external/glm-master/test")
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/external/glm-master/util")
set(glm.includeDirectories "${CMAKE_BINARY_DIR}/external/glm-master/")
