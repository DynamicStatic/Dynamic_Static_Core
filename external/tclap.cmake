
set(tclap.includeDirectories "${CMAKE_CURRENT_LIST_DIR}/tclap/include/")
list(APPEND tclap.clutter "${tclap.includeDirectories}/MakeFile.am")
list(APPEND tclap.clutter "${tclap.includeDirectories}/tclap/MakeFile.am")
file(REMOVE_RECURSE ${tclap.clutter})
