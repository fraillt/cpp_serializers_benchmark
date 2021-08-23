set(yas_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/yas)
set(yas_INCLUDE ${yas_PREFIX}/src/yas_dep/include)
ExternalProject_Add(
        yas_dep
        PREFIX ${yas_PREFIX}
        URL "https://github.com/niXman/yas/archive/7.1.0.tar.gz"
        URL_MD5 "91b86037720a1971525e33bb62f20db7"
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
    add_dependencies(${ExampleName} yas_dep)
    target_include_directories(${ExampleName} PUBLIC ${yas_INCLUDE})
    target_link_libraries(${ExampleName} PRIVATE Testing::core)
    add_test(NAME test_${ExampleName} COMMAND ${ExampleName})
endforeach()
