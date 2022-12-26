
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
  ../include/add.hpp
  ../include/sub.hpp
)

add_library(cppsample_objects OBJECT
  add.cpp
  sub.cpp
  ${cppsample_headers}
)

target_include_directories(cppsample_objects
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PUBLIC ${CMAKE_BINARY_DIR}/src
)

if(BUILD_SHARED_LIBS)
  add_library(cppsample SHARED $<TARGET_OBJECTS:cppsample_objects>)
else()
  add_library(cppsample STATIC $<TARGET_OBJECTS:cppsample_objects>)
endif()

add_library(trav::cppsample ALIAS cppsample)

target_include_directories(cppsample
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PUBLIC ${CMAKE_BINARY_DIR}/src
)

include(GenerateExportHeader)
generate_export_header(cppsample)

set_property(TARGET cppsample
  PROPERTY PUBLIC_HEADER ${cppsample_headers}
)

set_target_properties(
  cppsample PROPERTIES
  SOVERSION 1
  Version   1.0.0
)

# https://www.youtube.com/watch?v=m0DwB4OvDXk
install(TARGETS cppsample
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT cppsample_Runtime
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT cppsample_Runtime
    NAMELINK_COMPONENT cppsample_Development
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT cppsample_Development
)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cppsample)
