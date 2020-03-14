
#==========================================
#  Copyright (c) 2016-2020 Dynamic_Static
#    Patrick Purcell
#      Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

# Dynamic_Static.Core CMake configuration
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(Dynamic_Static.Core VERSION 0.2.0)
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/")
set(externalDirectory "${CMAKE_CURRENT_LIST_DIR}/external/")
include("${externalDirectory}/Dynamic_Static.CMake/Dynamic_Static.ex.cmake")

# Options
option(DST_GLM_ENABLED "TODO : Documentation" ON)

# Dynamic_Static.Core library
set(includeDirectory "${CMAKE_CURRENT_LIST_DIR}/include.ex/")
set(includePath "${includeDirectory}/dynamic_static/core/")
DstAddStaticLibrary(
    target Dynamic_Static.Core
    includeDirectories
        "${includeDirectory}"
        "${externalDirectory}/glm/"

        "${CMAKE_CURRENT_LIST_DIR}/include/"

    includeFiles
        "${includePath}/math/defines.hpp"
        "${includePath}/math/transform.hpp"
        "${includePath}/math/utilities.hpp"
        "${includePath}/action.hpp"
        "${includePath}/callback.hpp"
        "${includePath}/defines.hpp"
        "${includePath}/math.hpp"
        "${includePath}/time.hpp"
        "${includePath}/to-string.hpp"
        "${includePath}/version.hpp"
        "${includePath}/win32-lean-and-mean.hpp"

        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Events/Delegate.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Events/Event.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Events/Subscribable.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Math/Colors.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Math/Defines.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Math/Transform.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Math/Utilities.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Threads/Semaphore.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Threads/ThreadPool.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Threads/ThreadUtilities.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Threads/Worker.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Action.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Algorithm.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Callback.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Component.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Defines.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Entity.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Events.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/File.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/FileSystem.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Math.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Memory.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/MoveNotifier.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/NonCopyable.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Random.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/SharedObject.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Span.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/StringUtilities.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/StringView.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Threads.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Time.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/TypeUtilities.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/VectorUtilities.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Version.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Win32LeanAndMean.hpp"
)