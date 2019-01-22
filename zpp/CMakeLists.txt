set(zpp_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/zpp)
set(zpp_INCLUDE ${zpp_PREFIX}/src/zpp_dep)
ExternalProject_Add(
        zpp_dep
        PREFIX ${zpp_PREFIX}
        URL "https://github.com/eyalz800/serializer/archive/v0.3.tar.gz"
        URL_MD5 "fce17fc1af629c373b4ec01b89d1b8a9"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
)

add_executable(zpp zpp.cpp ${SOURCE_FILES})
add_dependencies(zpp zpp_dep)
target_include_directories(zpp PUBLIC ${zpp_INCLUDE})
target_link_libraries(zpp PRIVATE Testing::core)
add_test(NAME test_zpp COMMAND zpp)
