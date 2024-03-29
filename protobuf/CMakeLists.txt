set(protobuf_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/protobuf)
set(protobuf_INCLUDE ${protobuf_PREFIX}/include)

set(protobuf_CONFIGURE_COMMAND_EXTRA "")
if(MSVC)
    set(protobuf_CONFIGURE_COMMAND_EXTRA "-Dprotobuf_MSVC_STATIC_RUNTIME=OFF")
endif()

ExternalProject_Add(
        protobuf_dep
        PREFIX ${protobuf_PREFIX}
        URL "https://github.com/protocolbuffers/protobuf/releases/download/v3.17.3/protobuf-cpp-3.17.3.tar.gz"
        URL_MD5 "3fe4c2647e0991c014a386a896d0a116"
        CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${protobuf_PREFIX}
            -DCMAKE_BUILD_TYPE=Release -Dprotobuf_BUILD_TESTS=OFF
            <SOURCE_DIR>/cmake
        LOG_UPDATE ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
)

set(protobuf_GENERATOR ${protobuf_PREFIX}/bin/protoc)
set(protobuf_LIB ${protobuf_PREFIX}/lib/libprotobuf$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX})
set(protobuf_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(protobuf_SCHEMA_FILE ${protobuf_SOURCE_DIR}/monster.proto)
set(protobuf_GENERATED_FILES ${protobuf_SOURCE_DIR}/monster.pb.h ${protobuf_SOURCE_DIR}/monster.pb.cc)

add_custom_command(
        DEPENDS ${protobuf_SCHEMA_FILE}
        COMMAND ${protobuf_GENERATOR}
        ARGS -I=${protobuf_SOURCE_DIR} --cpp_out=${protobuf_SOURCE_DIR}/ ${protobuf_SCHEMA_FILE}
        OUTPUT ${protobuf_GENERATED_FILES}
        COMMENT "Executing protobuf compiler")
set_source_files_properties(${protobuf_GENERATED_FILES} PROPERTIES GENERATED TRUE)

file(GLOB ExampleFiles ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(REMOVE_ITEM ExampleFiles ${protobuf_GENERATED_FILES})
foreach(ExampleFile ${ExampleFiles})
    get_filename_component(ExampleName ${ExampleFile} NAME_WE)

    add_executable(${ExampleName} ${ExampleFile} ${protobuf_GENERATED_FILES})
    add_dependencies(${ExampleName} protobuf_dep)
    target_include_directories(${ExampleName} PUBLIC ${protobuf_INCLUDE})
    target_link_libraries(${ExampleName} PRIVATE Testing::core ${protobuf_LIB})
    add_test(NAME test_${ExampleName} COMMAND ${ExampleName})
endforeach()
