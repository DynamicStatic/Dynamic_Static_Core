
# CMake configuration for Dynamic_Static.Core

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch64")
    set(GLFW_INCLUDE ${DYNAMIC_STATIC_CORE_EXTERNAL}/glfw3/include/)
else()
    set(GLFW_INCLUDE ${DYNAMIC_STATIC_CORE_EXTERNAL}/glfw-3.2.1/include/)
endif()

include_directories(
    ${DYNAMIC_STATIC_CORE_INCLUDE}
    ${GLFW_INCLUDE}
)

# include_directories(
#     ${DYNAMIC_STATIC_CORE_INCLUDE}
#     ${DYNAMIC_STATIC_CORE_EXTERNAL}/glfw-3.2.1/include/
# )

add_library(
    Dynamic_Static.Core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Core/Algorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Core/BinaryReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Core/IPrintable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Core/NotImplementedError.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Core/Object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Core/SharedObjectFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Core/StringUtilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Core/Threads.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Core/ToString.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Core/Version.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Math/Color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Math/Matrix4x4.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Math/Quaternion.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Math/Vector2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Math/Vector3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/Math/Vector4.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Directory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/File.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Input.Manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Keyboard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Keyboard.State.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Monitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Monitor.Mode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Mouse.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Mouse.State.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Path.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Point.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Resolution.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Win32LeanAndMean.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamic_Static/System/Window.cpp
)

set_target_properties(Dynamic_Static.Core PROPERTIES PREFIX "")

add_custom_command(
    TARGET Dynamic_Static.Core POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${PACKAGE_DIRECTORY}/include/
)
