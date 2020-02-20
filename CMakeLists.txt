cmake_minimum_required(VERSION 3.11)

project(matcher VERSION 0.0.1 LANGUAGES C CXX)

add_subdirectory(external/nolibc)
add_subdirectory(matcher)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  enable_testing()
  add_subdirectory(tests)
endif()
