# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/OpticalProject_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/OpticalProject_autogen.dir/ParseCache.txt"
  "OpticalProject_autogen"
  )
endif()
