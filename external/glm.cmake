
set(glm.includeDirectories "${CMAKE_CURRENT_LIST_DIR}/glm/")
file(GLOB glm.clutter "${glm.includeDirectories}/*")
list(REMOVE_ITEM glm.clutter "${glm.includeDirectories}/glm")
list(APPEND glm.clutter "${glm.includeDirectories}/glm/CMakeLists.txt")
file(REMOVE_RECURSE ${glm.clutter})
