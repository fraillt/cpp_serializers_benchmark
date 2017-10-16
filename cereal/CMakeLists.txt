set(cereal_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/cereal)
set(cereal_INCLUDE ${cereal_PREFIX}/src/cereal/include)
ExternalProject_Add(
        cereal
        PREFIX ${cereal_PREFIX}
        URL "https://github.com/USCiLab/cereal/archive/v1.2.2.tar.gz"
        URL_MD5 "4C56C7B9499DBA79404250EF9A040481"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
)

add_executable(test_cereal cereal.cpp ${SOURCE_FILES})
add_dependencies(test_cereal cereal)
target_include_directories(test_cereal PUBLIC ${cereal_INCLUDE})
