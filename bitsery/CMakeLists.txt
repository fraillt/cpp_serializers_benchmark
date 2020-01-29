
set(bitsery_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/bitsery)
set(bitsery_INCLUDE ${bitsery_PREFIX}/src/bitsery_dep/include)
ExternalProject_Add(
        bitsery_dep
        PREFIX ${bitsery_PREFIX}
        URL "https://github.com/fraillt/bitsery/archive/v5.0.3.tar.gz"
        URL_MD5 "2b97b61032431255de87df57cbc5cd30"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
)

file(GLOB ExampleFiles ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach(ExampleFile ${ExampleFiles})
    get_filename_component(ExampleName ${ExampleFile} NAME_WE)
    add_executable(${ExampleName} ${ExampleFile})
    add_dependencies(${ExampleName} bitsery_dep)
    target_include_directories(${ExampleName} PUBLIC ${bitsery_INCLUDE})
    target_link_libraries(${ExampleName} PRIVATE Testing::core)
    add_test(NAME test_${ExampleName} COMMAND ${ExampleName})
endforeach()
