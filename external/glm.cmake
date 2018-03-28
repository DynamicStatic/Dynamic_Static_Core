
set(glm.version 0.9.8.5)
file(
    DOWNLOAD https://github.com/g-truc/glm/archive/${glm.version}.zip
    "${DownloadsDirectory}/glm.zip"
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf "${DownloadsDirectory}/glm.zip"
    WORKING_DIRECTORY "${ExternalDirectory}/"
)

set(glm.includeDirectories "${ExternalDirectory}/glm-${glm.version}/")
file(GLOB glm.clutter "${glm.includeDirectories}/*")
list(REMOVE_ITEM glm.clutter "${glm.includeDirectories}/glm")
file(REMOVE_RECURSE ${glm.clutter})
