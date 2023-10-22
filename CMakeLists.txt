cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    fluxsort
    VERSION 0.1.0
    DESCRIPTION "fluxsort sorting algorithm"
    HOMEPAGE_URL "https://github.com/scandum/fluxsort"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    fluxsort_fluxsort
    source/fluxsort.cpp
)
add_library(fluxsort::fluxsort ALIAS fluxsort_fluxsort)

include(GenerateExportHeader)
generate_export_header(
    fluxsort_fluxsort
    BASE_NAME fluxsort
    EXPORT_FILE_NAME export/fluxsort/fluxsort_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(fluxsort_fluxsort PUBLIC FLUXSORT_STATIC_DEFINE)
endif()

set_target_properties(
    fluxsort_fluxsort PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME fluxsort
    OUTPUT_NAME fluxsort
)

target_include_directories(
    fluxsort_fluxsort ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    fluxsort_fluxsort SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(fluxsort_fluxsort PUBLIC cxx_std_17)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT fluxsort_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of fluxsort"
  )
endif()

include(cmake/dev-mode.cmake)
