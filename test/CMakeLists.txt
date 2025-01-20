cmake_minimum_required(VERSION 3.14)

project(fluxsortTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(fluxsort REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(fluxsort_test source/fluxsort_test.cpp)
target_link_libraries(fluxsort_test PRIVATE fluxsort::fluxsort)
target_compile_features(fluxsort_test PRIVATE cxx_std_20)

add_test(NAME fluxsort_test COMMAND fluxsort_test)

# ---- End-of-file commands ----

add_folders(Test)
