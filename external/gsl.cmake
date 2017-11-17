
include(ExternalProject)
ExternalProject_Add(
    gsl
    PREFIX external
    DOWNLOAD_DIR external/gsl
    URL https://github.com/Microsoft/GSL/archive/master.zip
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gsl SOURCE_DIR)
set(gsl.include "${SOURCE_DIR}/include/")
