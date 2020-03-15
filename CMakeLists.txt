
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
        "${includePath}/span.hpp"
        "${includePath}/time.hpp"
        "${includePath}/to-string.hpp"
        "${includePath}/version.hpp"
        "${includePath}/win32-lean-and-mean.hpp"

        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Events/Delegate.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Events/Event.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Events/Subscribable.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Math/Colors.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Math/Defines.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Math/Transform.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Math/Utilities.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Threads/Semaphore.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Threads/ThreadPool.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Threads/ThreadUtilities.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Threads/Worker.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Action.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Algorithm.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Callback.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Component.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Defines.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Entity.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Events.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/File.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/FileSystem.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Math.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Memory.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/MoveNotifier.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/NonCopyable.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Random.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/SharedObject.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Span.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/StringUtilities.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/StringView.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Threads.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Time.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/TypeUtilities.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/VectorUtilities.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Version.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/Core/Win32LeanAndMean.ex.hpp"
)
