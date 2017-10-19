
set(boost_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/boost)
set(boost_INCLUDE ${boost_PREFIX}/src/boost)
ExternalProject_Add(
        boost
        PREFIX ${boost_PREFIX}
        URL "http://netcologne.dl.sourceforge.net/project/boost/boost/1.65.1/boost_1_65_1.tar.gz"
        URL_MD5 "ee64fd29a3fe42232c6ac3c419e523cf"
        CONFIGURE_COMMAND ${boost_PREFIX}/src/boost/bootstrap.sh --with-libraries=serialization --prefix=${boost_PREFIX}
        BUILD_COMMAND ./bjam link=static cxxflags='-fPIC'
        INSTALL_COMMAND ./bjam link=static install
        BUILD_IN_SOURCE 1
        LOG_UPDATE ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
        LOG_INSTALL ON
)
set(boost_LIBRARIES ${boost_PREFIX}/lib/libboost_serialization.a)

add_executable(test_boost boost.cpp ${SOURCE_FILES} )
add_dependencies(test_boost boost)
target_include_directories(test_boost PUBLIC ${boost_INCLUDE})
target_link_libraries(test_boost ${boost_LIBRARIES})

