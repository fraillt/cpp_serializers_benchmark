set(cereal_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/cereal)
set(cereal_INCLUDE ${cereal_PREFIX}/src/cereal_dep/include)
ExternalProject_Add(
        cereal_dep
        PREFIX ${cereal_PREFIX}
        URL "https://github.com/USCiLab/cereal/archive/v1.3.0.tar.gz"
        URL_MD5 "4342e811f245403646c4175258f413f1"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
)

add_executable(cereal cereal.cpp ${SOURCE_FILES})
add_dependencies(cereal cereal_dep)
target_include_directories(cereal PUBLIC ${cereal_INCLUDE})
target_link_libraries(cereal PRIVATE Testing::core)
add_test(NAME test_cereal COMMAND cereal)