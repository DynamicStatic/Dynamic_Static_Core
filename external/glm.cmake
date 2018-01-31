
file(
    DOWNLOAD
    https://github.com/g-truc/glm/archive/master.zip
    # https://github.com/g-truc/glm/releases/download/0.9.8.5/glm-0.9.8.5.zip
    "${DownloadsDirectory}/glm-master.zip"
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf "${DownloadsDirectory}/glm-master.zip"
    WORKING_DIRECTORY "${ExternalDirectory}/"
)

set(glm.includeDirectories "${ExternalDirectory}/glm-master/")
file(GLOB glm.clutter "${glm.includeDirectories}/*")
list(REMOVE_ITEM glm.clutter "${glm.includeDirectories}/glm")
file(REMOVE_RECURSE ${glm.clutter})
