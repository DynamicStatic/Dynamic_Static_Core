
#==========================================
#  Copyright (c) 2016-2020 dynamic_static
#    Patrick Purcell
#      Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

# dynamic_static.Core CMake configuration
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(dynamic_static.core VERSION 0.2.0)
set(CMAKE_CXX_STANDARD 17)
option(DST_CORE_BUILD_TESTS "Build dynamic_static.core.tests" ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/")
set(externalDirectory "${CMAKE_CURRENT_LIST_DIR}/external/")

################################################################################
include("${CMAKE_CURRENT_LIST_DIR}/../dynamic_static.build/dynamic_static.cmake")
# include("${externalDirectory}/cmake/dynamic_static.cmake")
################################################################################

# Options
option(DST_GLM_ENABLED "TODO : Documentation" ON)

# dynamic_static.core library
set(includeDirectory "${CMAKE_CURRENT_LIST_DIR}/include/")
set(includePath "${includeDirectory}/dynamic_static/core/")
dst_add_static_library(
    target dynamic_static.core
    includeDirectories
        PUBLIC
            "${externalDirectory}/glm/"
            "${includeDirectory}"
    includeFiles
        "${includePath}/action.hpp"
        "${includePath}/algorithm.hpp"
        "${includePath}/defines.hpp"
        "${includePath}/delegate.hpp"
        "${includePath}/enum.hpp"
        "${includePath}/event.hpp"
        "${includePath}/file.hpp"
        "${includePath}/math.hpp"
        "${includePath}/memory.hpp"
        "${includePath}/random.hpp"
        "${includePath}/span.hpp"
        "${includePath}/stream-guard.hpp"
        "${includePath}/string.hpp"
        "${includePath}/subscribable.hpp"
        "${includePath}/tab.hpp"
        "${includePath}/thread-pool.hpp"
        "${includePath}/time.hpp"
        "${includePath}/transform.hpp"
        "${includePath}/vector.hpp"
        "${includePath}/version.hpp"
        "${includePath}/win32-lean-and-mean.hpp"
        "${includeDirectory}/dynamic_static.core.hpp"
    sourceFiles
        "${CMAKE_CURRENT_LIST_DIR}/dynamic_static.core.cpp"
)

# dynamic_static.core.tests
if(DST_CORE_BUILD_TESTS)
    set(testsPath "${CMAKE_CURRENT_LIST_DIR}/tests/")
    dst_add_target_test_suite(
        target dynamic_static.core
        sourceFiles
            "${testsPath}/delegate.tests.cpp"
            "${testsPath}/enum.tests.cpp"
            "${testsPath}/event.tests.cpp"
            "${testsPath}/random.tests.cpp"
            "${testsPath}/span.tests.cpp"
            "${testsPath}/stream-guard.tests.cpp"
            "${testsPath}/string.tests.cpp"
            "${testsPath}/subscribable.tests.cpp"
            "${testsPath}/thread-pool.tests.cpp"
            "${testsPath}/vector.tests.cpp"
    )
endif()
