cmake_minimum_required(VERSION 3.5)
project(bitsery_benchmark)

#################################################
# configure required depencendies
#################################################

include(ExternalProject)

#bitsery
set(bitsery_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/cereal)
set(bitsery_INCLUDE ${bitsery_PREFIX}/src/bitsery/include)
ExternalProject_Add(
        bitsery
        PREFIX ${bitsery_PREFIX}
        URL "https://github.com/fraillt/bitsery/archive/v4.0.0.tar.gz"
        URL_MD5 "A5B2102A6177661BCE5DDBCD9C982006"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
)
#add cereal
set(cereal_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/cereal)
set(cereal_INCLUDE ${cereal_PREFIX}/src/cereal/include)
ExternalProject_Add(
        cereal
        PREFIX ${cereal_PREFIX}
        URL "https://github.com/USCiLab/cereal/archive/v1.2.2.tar.gz"
        URL_MD5 "4C56C7B9499DBA79404250EF9A040481"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
)

#add yas
set(yas_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/yas)
set(yas_INCLUDE ${yas_PREFIX}/src/yas/include)
ExternalProject_Add(
        yas
        PREFIX ${yas_PREFIX}
        URL "https://github.com/niXman/yas/archive/5.0.zip"
        URL_MD5 "1acaef7cb8ab4178453dfa67a0112ea8"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
)

#add flatbuffers
set(flatbuffers_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/flatbuffers)
set(flatbuffers_INCLUDE ${flatbuffers_PREFIX}/include)
ExternalProject_Add(
        flatbuffers
        PREFIX ${flatbuffers_PREFIX}
        URL "https://github.com/google/flatbuffers/archive/v1.7.1.tar.gz"
        URL_MD5 "81934736f31fbd2cfdb513e71b53b358"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${flatbuffers_PREFIX} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        LOG_UPDATE ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
)

set(flatbuffers_GENERATOR ${flatbuffers_PREFIX}/bin/flatc)
set(flatbuffers_SOURCE_DIR ${CMAKE_SOURCE_DIR}/flatbuffers)
set(flatbuffers_SCHEMA_FILE ${flatbuffers_SOURCE_DIR}/monster.fbs)
set(flatbuffers_GENERATED_FILE ${flatbuffers_SOURCE_DIR}/monster_generated.h)
add_custom_command(
        DEPENDS ${flatbuffers_SCHEMA_FILE}
        COMMAND ${flatbuffers_GENERATOR}
        ARGS --cpp -o ${flatbuffers_SOURCE_DIR}/ ${flatbuffers_SCHEMA_FILE}
        OUTPUT ${flatbuffers_GENERATED_FILE}
        COMMENT "Executing FlatBuffers compiler")
set_source_files_properties(${flatbuffers_GENERATED_FILE} PROPERTIES GENERATED TRUE)


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

# set common sources
include_directories(./)
set(SOURCE_FILES
        testing_core/types.cpp
        testing_core/types.h
        testing_core/test.cpp
        testing_core/test.h
        )



#################################################
# configure executables
#################################################


#hand written
add_executable(test_hand_written hand_written/hand_written.cpp ${SOURCE_FILES})
add_executable(test_hand_written_no_checking hand_written/hand_written_no_checking.cpp ${SOURCE_FILES})

#bitsery
add_executable(test_bitsery bitsery/bitsery.cpp ${SOURCE_FILES} )
add_dependencies(test_bitsery bitsery)
target_include_directories(test_bitsery PUBLIC ${bitsery_INCLUDE})

add_executable(test_bitsery_fixed_buffer ./bitsery/bitsery_fixed_buffer.cpp ${SOURCE_FILES})
add_dependencies(test_bitsery_fixed_buffer bitsery)
target_include_directories(test_bitsery_fixed_buffer PUBLIC ${bitsery_INCLUDE})

add_executable(test_bitsery_sstream bitsery/bitsery_sstream.cpp ${SOURCE_FILES})
add_dependencies(test_bitsery_sstream bitsery)
target_include_directories(test_bitsery_sstream PUBLIC ${bitsery_INCLUDE})

add_executable(test_bitsery_compatibility bitsery/bitsery_compatibility.cpp ${SOURCE_FILES})
add_dependencies(test_bitsery_compatibility bitsery)
target_include_directories(test_bitsery_compatibility PUBLIC ${bitsery_INCLUDE})

add_executable(test_bitsery_compression bitsery/bitsery_compression.cpp ${SOURCE_FILES})
add_dependencies(test_bitsery_compression bitsery)
target_include_directories(test_bitsery_compression PUBLIC ${bitsery_INCLUDE})

add_executable(test_bitsery_verbose_syntax bitsery/bitsery_verbose_syntax.cpp ${SOURCE_FILES})
add_dependencies(test_bitsery_verbose_syntax bitsery)
target_include_directories(test_bitsery_verbose_syntax PUBLIC ${bitsery_INCLUDE})

#cereal
add_executable(test_cereal cereal/cereal.cpp ${SOURCE_FILES})
add_dependencies(test_cereal cereal)
target_include_directories(test_cereal PUBLIC ${cereal_INCLUDE})

#yas
add_executable(test_yas yas/yas.cpp ${SOURCE_FILES})
add_dependencies(test_yas yas)
target_include_directories(test_yas PUBLIC ${yas_INCLUDE})

add_executable(test_yas_compression yas/yas_compression.cpp ${SOURCE_FILES})
add_dependencies(test_yas_compression yas)
target_include_directories(test_yas_compression PUBLIC ${yas_INCLUDE})

add_executable(test_yas_sstream yas/yas_sstream.cpp ${SOURCE_FILES})
add_dependencies(test_yas_sstream yas)
target_include_directories(test_yas_sstream PUBLIC ${yas_INCLUDE})

#flatbuffers
add_executable(test_flatbuffers flatbuffers/flatbuffers.cpp ${SOURCE_FILES} ${flatbuffers_GENERATED_FILE})
add_dependencies(test_flatbuffers flatbuffers)
target_include_directories(test_flatbuffers PUBLIC ${flatbuffers_INCLUDE})



