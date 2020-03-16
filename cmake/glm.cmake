
#==========================================
#  Copyright (c) 2016-2020 Dynamic_Static
#    Patrick Purcell
#      Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

set(glm_includeDirectories "${CMAKE_CURRENT_LIST_DIR}/glm/")
file(GLOB glm_clutter "${glm_includeDirectories}/*")
list(REMOVE_ITEM glm_clutter "${glm_includeDirectories}/glm/")
list(APPEND glm_clutter "${glm_includeDirectories}/glm/CMakeLists.txt")
file(REMOVE_RECURSE ${glm_clutter})
