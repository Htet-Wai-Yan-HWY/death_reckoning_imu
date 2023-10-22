# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_death_reckoning_imu_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED death_reckoning_imu_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(death_reckoning_imu_FOUND FALSE)
  elseif(NOT death_reckoning_imu_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(death_reckoning_imu_FOUND FALSE)
  endif()
  return()
endif()
set(_death_reckoning_imu_CONFIG_INCLUDED TRUE)

# output package information
if(NOT death_reckoning_imu_FIND_QUIETLY)
  message(STATUS "Found death_reckoning_imu: 0.0.0 (${death_reckoning_imu_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'death_reckoning_imu' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${death_reckoning_imu_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(death_reckoning_imu_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${death_reckoning_imu_DIR}/${_extra}")
endforeach()