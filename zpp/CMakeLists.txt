set(zpp_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/zpp)
set(zpp_INCLUDE ${zpp_PREFIX}/src/zpp_dep)
ExternalProject_Add(
        zpp_dep
        PREFIX ${zpp_PREFIX}
        URL "https://github.com/eyalz800/serializer/archive/v0.1.tar.gz"
        URL_MD5 "96f1db7d8f80917d730cbb1a8d7f2fbe"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
)

add_executable(zpp zpp.cpp ${SOURCE_FILES})
add_dependencies(zpp zpp_dep)
target_include_directories(zpp PUBLIC ${zpp_INCLUDE})
target_link_libraries(zpp PRIVATE Testing::core)
add_test(NAME test_zpp COMMAND zpp)
