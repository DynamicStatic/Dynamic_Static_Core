
# ==========================================
#   Copyright (c) 2020 dynamic_static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

include(FetchContent)
FetchContent_Declare(
    glm
    GIT_REPOSITORY "https://github.com/g-truc/glm.git"
    GIT_TAG 0.9.9.8
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(glm)
