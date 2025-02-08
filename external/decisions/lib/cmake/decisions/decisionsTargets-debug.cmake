#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "decisions::decisions" for configuration "Debug"
set_property(TARGET decisions::decisions APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(decisions::decisions PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/decisions.lib"
  )

list(APPEND _cmake_import_check_targets decisions::decisions )
list(APPEND _cmake_import_check_files_for_decisions::decisions "${_IMPORT_PREFIX}/lib/decisions.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
