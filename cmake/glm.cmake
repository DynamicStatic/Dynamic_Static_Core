
#==========================================
#  Copyright (c) 2016-2020 Dynamic_Static
#    Patrick Purcell
#      Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

set(glmIncludeDirectory "${CMAKE_CURRENT_LIST_DIR}/glm/")
file(GLOB glmClutter "${glmIncludeDirectory}/*")
list(REMOVE_ITEM glmClutter "${glmIncludeDirectory}/glm/")
list(APPEND glmClutter "${glmIncludeDirectory}/glm/CMakeLists.txt")
file(REMOVE_RECURSE ${glmClutter})
