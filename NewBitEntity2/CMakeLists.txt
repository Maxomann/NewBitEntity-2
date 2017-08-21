cmake_minimum_required(VERSION 3.8)
project(NewBitEntity2)
enable_testing()
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/std:c++latest>)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/W4>)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/wd4100>)

if(NOT SMART_SIGNALS_ROOT)
    message(FATAL_ERROR "SMART_SIGNALS_ROOT not defined")
endif(NOT SMART_SIGNALS_ROOT)

include_directories(NewBitEntity2 PUBLIC "${SMART_SIGNALS_ROOT}/include")

FILE(GLOB HEADER_FILES src/*.h)
FILE(GLOB SOURCE_FILES src/*.cpp)
add_library(NewBitEntity2 STATIC ${HEADER_FILES} ${SOURCE_FILES})

include_directories(/)

FILE(GLOB HEADER_FILES test/General/*.h)
FILE(GLOB SOURCE_FILES test/General/*.cpp)
add_executable(Test_General ${HEADER_FILES} ${SOURCE_FILES})
add_dependencies(Test_General NewBitEntity2)
target_link_libraries(Test_General NewBitEntity2)

add_test(General Test_General)
