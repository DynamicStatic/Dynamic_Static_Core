
set(gsl.commitHash d846fe50a3f0bb7767c7e087a05f4be95f4da0ec)
file(
    DOWNLOAD https://github.com/Microsoft/GSL/archive/${gsl.commitHash}.zip
    "${DownloadsDirectory}/GSL.zip"
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf "${DownloadsDirectory}/GSL.zip"
    WORKING_DIRECTORY "${ExternalDirectory}/"
)

set(gsl.includeDirectories "${ExternalDirectory}/GSL-${gsl.commitHash}/include/")
