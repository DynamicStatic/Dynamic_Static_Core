
file(
    DOWNLOAD
    https://github.com/Microsoft/GSL/archive/master.zip
    "${DownloadsDirectory}/GSL-master.zip"
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf "${DownloadsDirectory}/GSL-master.zip"
    WORKING_DIRECTORY "${ExternalDirectory}/"
)

set(gsl.includeDirectories "${ExternalDirectory}/GSL-master/include/")
