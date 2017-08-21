cmake_minimum_required(VERSION 3.8)
include(ExternalProject)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/std:c++latest>)

message(${CMAKE_SOURCE_DIR})

ExternalProject_Add(SmartSignals
  GIT_REPOSITORY git://github.com/Maxomann/SmartSignals.git

  INSTALL_DIR ${CMAKE_SOURCE_DIR}\\${INSTALL_NAME}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
)
