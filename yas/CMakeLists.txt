set(yas_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/yas)
set(yas_INCLUDE ${yas_PREFIX}/src/yas/include)
ExternalProject_Add(
        yas
        PREFIX ${yas_PREFIX}
        URL "https://github.com/niXman/yas/archive/5.0.zip"
        URL_MD5 "1acaef7cb8ab4178453dfa67a0112ea8"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
)


add_executable(test_yas yas.cpp ${SOURCE_FILES})
add_dependencies(test_yas yas)
target_include_directories(test_yas PUBLIC ${yas_INCLUDE})

add_executable(test_yas_compression yas_compression.cpp ${SOURCE_FILES})
add_dependencies(test_yas_compression yas)
target_include_directories(test_yas_compression PUBLIC ${yas_INCLUDE})

add_executable(test_yas_sstream yas_sstream.cpp ${SOURCE_FILES})
add_dependencies(test_yas_sstream yas)
target_include_directories(test_yas_sstream PUBLIC ${yas_INCLUDE})
