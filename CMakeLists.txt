cmake_minimum_required(VERSION 3.20)

project(cppsample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Use -std=c++17 instead of -std=gnu++17
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


option(USE_LTO "Enable Link-Time Optimization for Release builds" ON)
option(BUILD_TESTS "Build the tests" ON)

# https://www.kitware.com/cmake-and-the-default-build-type/
# Set a default build type if none was specified
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
    STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Enable colored warnings in Ninja's output, if the compiler has -fdiagnostics-color support.
# https://github.com/ninja-build/ninja/issues/174
if(CMAKE_GENERATOR STREQUAL "Ninja")
  add_compile_options($<$<COMPILE_LANG_AND_ID:C,GNU>:$<$<VERSION_GREATER_EQUAL:$<C_COMPILER_VERSION>,4.9>:-fdiagnostics-color=always>>)
  add_compile_options($<$<COMPILE_LANG_AND_ID:CXX,GNU>:$<$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,4.9>:-fdiagnostics-color=always>>)
  add_compile_options($<$<COMPILE_LANG_AND_ID:C,Clang>:$<$<VERSION_GREATER_EQUAL:$<C_COMPILER_VERSION>,3.5>:-fcolor-diagnostics>>)
  add_compile_options($<$<COMPILE_LANG_AND_ID:CXX,Clang>:$<$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,3.5>:-fcolor-diagnostics>>)
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

if(MSVC)
  add_compile_options(/utf-8 /W4 /WX)
  add_compile_options($<$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,19.10>:/permissive->)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(USE_LTO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT ipo_result OUTPUT ipo_output)
  if(ipo_result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE)
    message(STATUS "Link-time Optimization enabled for release builds")
  else()
    message(FATAL_ERROR "IPO is not supported: ${ipo_output}")
  endif()
else()
message(STATUS "Link-time Optimization disabled")
endif()

add_subdirectory(src)

if(BUILD_TESTS)
  find_package(GTest CONFIG REQUIRED
    NO_DEFAULT_PATH
    PATHS ${CMAKE_BINARY_DIR}
  )
  add_subdirectory(test)
endif()
