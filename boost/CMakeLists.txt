
set(boost_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/boost)
set(boost_INCLUDE ${boost_PREFIX}/src/boost_dep)

if( UNIX )
    set( boost_CMDbootstrap bootstrap.sh )
    set( boost_CMDb2 b2 )
else()
    message(WARNING "boost building implemented only on unix")
    return()
endif()

set(boost_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/boost)
set(boost_INCLUDE ${boost_PREFIX}/src/boost_dep)
ExternalProject_Add(
        boost_dep
        PREFIX ${boost_PREFIX}
        URL "https://boostorg.jfrog.io/artifactory/main/release/1.77.0/source/boost_1_77_0.tar.gz"
        URL_MD5 "5e07d6aa387ba780e4e4de85b5ba3c70"
        CONFIGURE_COMMAND ${boost_PREFIX}/src/boost_dep/${boost_CMDbootstrap} --with-libraries=serialization --prefix=${boost_PREFIX}
        BUILD_COMMAND ./${boost_CMDb2} --with-serialization
        INSTALL_COMMAND ""
        BUILD_IN_SOURCE 1
        LOG_UPDATE ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
        LOG_INSTALL ON
)

add_executable(boost boost.cpp)
add_dependencies(boost boost_dep)
target_include_directories(boost PUBLIC ${boost_INCLUDE})
target_link_libraries(boost PRIVATE Testing::core ${boost_INCLUDE}/stage/lib/libboost_serialization.a)

add_test(NAME test_boost COMMAND boost)
