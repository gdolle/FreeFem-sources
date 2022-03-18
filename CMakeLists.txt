cmake_minimum_required(VERSION 3.18)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(FreeFEM
        VERSION 4.10.0
        DESCRIPTION "A high level multiphysics finite element software"
        LANGUAGES C CXX Fortran)

file(GLOB FF_CMAKE_MODULES ${CMAKE_SOURCE_DIR}/cmake/*/)
list(APPEND CMAKE_MODULE_PATH ${FF_CMAKE_MODULES})

include(ff_configure_compilers)

include(ff_configure_thirdparty)
include(ff_write_config_file)

ff_configure_cmake()
ff_configure_compilers()
ff_configure_thirdparty()

ff_write_config_file()

# Enable CTest.
enable_testing()

add_subdirectory(src)
add_subdirectory(examples)
