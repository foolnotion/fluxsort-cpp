if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/fluxsort-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package fluxsort)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT fluxsort_Development
)

install(
    TARGETS fluxsort_fluxsort
    EXPORT fluxsortTargets
    RUNTIME #
    COMPONENT fluxsort_Runtime
    LIBRARY #
    COMPONENT fluxsort_Runtime
    NAMELINK_COMPONENT fluxsort_Development
    ARCHIVE #
    COMPONENT fluxsort_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    fluxsort_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(fluxsort_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${fluxsort_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT fluxsort_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${fluxsort_INSTALL_CMAKEDIR}"
    COMPONENT fluxsort_Development
)

install(
    EXPORT fluxsortTargets
    NAMESPACE fluxsort::
    DESTINATION "${fluxsort_INSTALL_CMAKEDIR}"
    COMPONENT fluxsort_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
