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


add_executable(test_flatbuffers flatbuffers.cpp ${SOURCE_FILES} ${flatbuffers_GENERATED_FILE})
add_dependencies(test_flatbuffers flatbuffers)
target_include_directories(test_flatbuffers PUBLIC ${flatbuffers_INCLUDE})
