#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "dynamic_staticdynamic_static.core" for configuration "Debug"
set_property(TARGET dynamic_staticdynamic_static.core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(dynamic_staticdynamic_static.core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/dynamic_static.core.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS dynamic_staticdynamic_static.core )
list(APPEND _IMPORT_CHECK_FILES_FOR_dynamic_staticdynamic_static.core "${_IMPORT_PREFIX}/lib/dynamic_static.core.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
