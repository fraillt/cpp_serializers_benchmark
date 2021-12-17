set(zpp_bits_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/zpp_bits)
set(zpp_bits_INCLUDE ${zpp_bits_PREFIX}/src/zpp_bits_dep)
ExternalProject_Add(
        zpp_bits_dep
        PREFIX ${zpp_bits_PREFIX}
        URL "https://github.com/eyalz800/zpp_bits/archive/v2.0.tar.gz"
        URL_MD5 "29a45464678584858407a0699ea835b6"
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
    add_dependencies(${ExampleName} zpp_bits_dep)
    target_include_directories(${ExampleName} PUBLIC ${zpp_bits_INCLUDE})
    target_link_libraries(${ExampleName} PRIVATE Testing::core)
    add_test(NAME test_${ExampleName} COMMAND ${ExampleName})
endforeach()
