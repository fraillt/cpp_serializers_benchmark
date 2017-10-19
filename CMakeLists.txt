cmake_minimum_required(VERSION 3.5)
project(cpp_serializers_benchmark)

#################################################
# configure required depencendies
#################################################

include(ExternalProject)

#################################################
# configure compiler and set default compile options
#################################################

#default definitions
add_definitions(-DNDEBUG)
add_definitions(-DMONSTERS=50)
add_definitions(-DSAMPLES=300000)

# compiler
set(CMAKE_CXX_STANDARD 14)
# we only care about -O2
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# set common sources,
include_directories(${CMAKE_SOURCE_DIR}/)
set(SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/testing_core/types.cpp
        ${CMAKE_SOURCE_DIR}/testing_core/types.h
        ${CMAKE_SOURCE_DIR}/testing_core/test.cpp
        ${CMAKE_SOURCE_DIR}/testing_core/test.h
        )

#################################################
# configure executables
#################################################

add_subdirectory(bitsery)
add_subdirectory(boost)
add_subdirectory(cereal)
add_subdirectory(flatbuffers)
add_subdirectory(hand_written)
add_subdirectory(yas)
