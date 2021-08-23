set(zpp_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/zpp)
set(zpp_INCLUDE ${zpp_PREFIX}/src/zpp_dep)
ExternalProject_Add(
        zpp_dep
        PREFIX ${zpp_PREFIX}
        URL "https://github.com/eyalz800/serializer/archive/v0.4.tar.gz"
        URL_MD5 "c670ff18478122826ac13edbe9711cdc"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        CMAKE_ARGS -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD} -DCMAKE_C_COMPILER='${CMAKE_C_COMPILER}' -DCMAKE_CXX_COMPILER='${CMAKE_CXX_COMPILER}' -DCMAKE_SYSTEM_PROCESSOR=${DCMAKE_SYSTEM_PROCESSOR}
          -DCMAKE_ASM_FLAGS='${CMAKE_ASM_FLAGS}' -DCMAKE_LINK_FLAGS='${CMAKE_LINK_FLAGS}'
)

add_executable(zpp zpp.cpp ${SOURCE_FILES})
add_dependencies(zpp zpp_dep)
target_include_directories(zpp PUBLIC ${zpp_INCLUDE})
target_link_libraries(zpp PRIVATE Testing::core)
add_test(NAME test_zpp COMMAND zpp)
