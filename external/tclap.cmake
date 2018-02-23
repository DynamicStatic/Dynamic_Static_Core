
file(
    DOWNLOAD
    https://github.com/mirror/tclap/archive/v1.2.2.zip
    "${DownloadsDirectory}/tclap.zip"
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf "${DownloadsDirectory}/tclap.zip"
    WORKING_DIRECTORY "${ExternalDirectory}/"
)

set(tclap.includeDirectories "${ExternalDirectory}/tclap-1.2.2/include/")
file(REMOVE_RECURSE "${tclap.includeDirectories}/MakeFile.am")
file(REMOVE_RECURSE "${tclap.includeDirectories}/tclap/MakeFile.am")
