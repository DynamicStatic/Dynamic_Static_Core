
# CMake configuration for Dynamic_Static.Core/Sandbox

include_directories(
    include/
    ${DYNAMIC_STATIC_CORE_INCLUDE}
)

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch64")
    set(GLFW_LIBRARY ${DYNAMIC_STATIC_CORE_EXTERNAL}/glfw3/libs/)
    message(STATUS "GLFW LIB : ${GLFW_LIBRARY}")
else()

endif()

link_directories(${GLFW_LIBRARY})
add_executable(
    Dynamic_Static.Core.Sandbox
    ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
)

include_directories(
    ${DYNAMIC_STATIC_CORE_INCLUDE}
    ${GLFW_INCLUDE}
)

# find_package(glfw)

target_link_libraries(
    Dynamic_Static.Core.Sandbox
    Dynamic_Static.Core
    # glfw ${GLFW_LIBRARIES}
    


    glfw3
    GL
    X11
    Xxf86vm
    Xrandr
    pthread
    Xi

    # X11
    
 
)

# message(STATUS "GLFW libraries : ${GLFW_LIBRARIES}")
