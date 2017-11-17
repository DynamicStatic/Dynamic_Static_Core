
include(ExternalProject)
ExternalProject_Add(
    glm
    PREFIX external
    DOWNLOAD_DIR external/glm
    URL https://github.com/g-truc/glm/archive/master.zip
    # URL https://github.com/g-truc/glm/releases/download/0.9.8.5/glm-0.9.8.5.zip
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(glm SOURCE_DIR)
file(REMOVE_RECURSE "${SOURCE_DIR}/cmake/")
file(REMOVE_RECURSE "${SOURCE_DIR}/doc/")
file(REMOVE_RECURSE "${SOURCE_DIR}/test/")
file(REMOVE_RECURSE "${SOURCE_DIR}/util/")
set(glm.include "${SOURCE_DIR}/")
