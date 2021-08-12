
set(msgpack_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/msgpack)
set(msgpack_INCLUDE ${msgpack_PREFIX}/src/msgpack_dep/include)
ExternalProject_Add(
        msgpack_dep
        PREFIX ${msgpack_PREFIX}
        URL "https://github.com/msgpack/msgpack-c/releases/download/cpp-3.3.0/msgpack-3.3.0.tar.gz"
        URL_MD5 "e676575d52caae974e579c3d5f0ba6a2"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        CMAKE_ARGS -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD} -DCMAKE_C_COMPILER='${CMAKE_C_COMPILER}' -DCMAKE_CXX_COMPILER='${CMAKE_CXX_COMPILER}' -DCMAKE_SYSTEM_PROCESSOR=${DCMAKE_SYSTEM_PROCESSOR}
          -DCMAKE_ASM_FLAGS='${CMAKE_ASM_FLAGS}' -DCMAKE_LINK_FLAGS='${CMAKE_LINK_FLAGS}'
)

file(GLOB ExampleFiles ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach(ExampleFile ${ExampleFiles})
    get_filename_component(ExampleName ${ExampleFile} NAME_WE)
    add_executable(${ExampleName} ${ExampleFile})
    add_dependencies(${ExampleName} msgpack_dep)
    target_include_directories(${ExampleName} PUBLIC ${msgpack_INCLUDE})
    target_link_libraries(${ExampleName} PRIVATE Testing::core)
    add_test(NAME test_${ExampleName} COMMAND ${ExampleName})
endforeach()
