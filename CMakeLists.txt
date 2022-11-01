cmake_minimum_required(VERSION 3.20)

project(cppsample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Use -std=c++17 instead of -std=gnu++17
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

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
if (CMAKE_GENERATOR STREQUAL "Ninja")
  add_compile_options($<$<COMPILE_LANG_AND_ID:C,GNU>:$<$<VERSION_GREATER_EQUAL:$<C_COMPILER_VERSION>,4.9>:-fdiagnostics-color=always>>)
  add_compile_options($<$<COMPILE_LANG_AND_ID:CXX,GNU>:$<$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,4.9>:-fdiagnostics-color=always>>)
  add_compile_options($<$<COMPILE_LANG_AND_ID:C,Clang>:$<$<VERSION_GREATER_EQUAL:$<C_COMPILER_VERSION>,3.5>:-fcolor-diagnostics>>)
  add_compile_options($<$<COMPILE_LANG_AND_ID:CXX,Clang>:$<$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,3.5>:-fcolor-diagnostics>>)
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_result OUTPUT ipo_output)
if(ipo_result)
  set(INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
  message(WARNING "IPO is not supported: ${ipo_output}")
endif()

if(NOT APPLE)
  set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

set(cppsample_headers
  add.hpp
  export.hpp
)

add_library(cppsample_objects OBJECT
  add.cpp
  ${cppsample_headers}
)

if(MSVC)
  add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:/utf-8>)
  if (MSVC_VERSION GREATER_EQUAL 1910)
    add_compile_options(cppsample_objects PUBLIC $<$<COMPILE_LANGUAGE:C,CXX>:/permissive->)
  endif()
  target_compile_options(cppsample_objects PRIVATE /W4 /WX)
else()
  target_compile_options(cppsample_objects PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_compile_definitions(cppsample_objects PRIVATE CPPSAMPLE_BUILD)

if(BUILD_SHARED_LIBS)
  add_library(cppsample SHARED $<TARGET_OBJECTS:cppsample_objects>)
else()
  add_library(cppsample STATIC $<TARGET_OBJECTS:cppsample_objects>)
endif()

add_library(trav::cppsample ALIAS cppsample)

set_property(TARGET cppsample
  PROPERTY PUBLIC_HEADER ${cppsample_headers}
)

set_target_properties(
  cppsample PROPERTIES
  SOVERSION 1
  Version   1.0.0
)

install(TARGETS cppsample
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT cppsample_Runtime
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT cppsample_Runtime
    NAMELINK_COMPONENT cppsample_Development
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT cppsample_Development
)
