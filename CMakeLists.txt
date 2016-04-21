cmake_minimum_required (VERSION 2.6)
project (DeusExHRSaveIndexer)
# The version number.
set (Tutorial_VERSION_MAJOR 0)
set (Tutorial_VERSION_MINOR 1)

set(SOURCES
    indexfile.hpp
    indexfile.cpp
    indexer.cpp
)

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")
set (CMAKE_EXE_LINKER_FLAGS "-std=c++11")

add_executable(indexer ${SOURCES})
