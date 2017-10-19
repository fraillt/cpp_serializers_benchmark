
set(bitsery_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/bitsery)
set(bitsery_INCLUDE ${bitsery_PREFIX}/src/bitsery/include)
ExternalProject_Add(
        bitsery
        PREFIX ${bitsery_PREFIX}
        URL "https://github.com/fraillt/bitsery/archive/v4.0.0.tar.gz"
        URL_MD5 "a5b2102a6177661bce5ddbcd9c982006"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
)

add_executable(test_bitsery bitsery.cpp ${SOURCE_FILES} )
add_dependencies(test_bitsery bitsery)
target_include_directories(test_bitsery PUBLIC ${bitsery_INCLUDE})

add_executable(test_bitsery_fixed_buffer bitsery_fixed_buffer.cpp ${SOURCE_FILES})
add_dependencies(test_bitsery_fixed_buffer bitsery)
target_include_directories(test_bitsery_fixed_buffer PUBLIC ${bitsery_INCLUDE})

add_executable(test_bitsery_sstream bitsery_sstream.cpp ${SOURCE_FILES})
add_dependencies(test_bitsery_sstream bitsery)
target_include_directories(test_bitsery_sstream PUBLIC ${bitsery_INCLUDE})

add_executable(test_bitsery_compatibility bitsery_compatibility.cpp ${SOURCE_FILES})
add_dependencies(test_bitsery_compatibility bitsery)
target_include_directories(test_bitsery_compatibility PUBLIC ${bitsery_INCLUDE})

add_executable(test_bitsery_compression bitsery_compression.cpp ${SOURCE_FILES})
add_dependencies(test_bitsery_compression bitsery)
target_include_directories(test_bitsery_compression PUBLIC ${bitsery_INCLUDE})

add_executable(test_bitsery_verbose_syntax bitsery_verbose_syntax.cpp ${SOURCE_FILES})
add_dependencies(test_bitsery_verbose_syntax bitsery)
target_include_directories(test_bitsery_verbose_syntax PUBLIC ${bitsery_INCLUDE})
