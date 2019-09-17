set(yas_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/yas)
set(yas_INCLUDE ${yas_PREFIX}/src/yas_dep/include)
ExternalProject_Add(
        yas_dep
        PREFIX ${yas_PREFIX}
        URL "https://github.com/niXman/yas/archive/7.0.4.tar.gz"
        URL_MD5 "e548556552d5a8d3aa634eda1621d027"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
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
