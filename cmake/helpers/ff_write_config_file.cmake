include(CMakePackageConfigHelpers)

function(ff_write_config_file)

  # Third-party libraries
  foreach(PACKAGE ${MODULE_LIST})
    set(FREEFEM_${PACKAGE}_INCLUDE_PATHS ${FREEFEM_${PACKAGE}_INCLUDE_PATHS}) 
    set(FREEFEM_${PACKAGE}_LIBRARIES ${FREEFEM_${PACKAGE}_LIBRARIES})
    list(APPEND FF_PKG_VARS FREEFEM_${PACKAGE}_INCLUDE_PATHS FREEFEM_${PACKAGE}_LIBRARIES)
  endforeach(PACKAGE)


  configure_package_config_file(
    ${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}/cmake
    PATH_VARS CMAKE_C_COMPILER CMAKE_C_FLAGS CMAKE_CXX_COMPILER CMAKE_CXX_FLAGS ${FF_PKG_VARS}
  )
  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${CMAKE_PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion 
  )

endfunction(ff_write_config_file)

