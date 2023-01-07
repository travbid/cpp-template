
if(NOT APPLE)
  set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

set(cppsample_headers
  ../include/add.hpp
  ../include/sub.hpp
)

set(cppsample_sources
  add.cpp
  sub.cpp
  ${cppsample_headers}
)

if(BUILD_SHARED_LIBS)
  add_library(cppsample SHARED ${cppsample_sources})
else()
  add_library(cppsample STATIC ${cppsample_sources})
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

install(TARGETS main
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT main
)
