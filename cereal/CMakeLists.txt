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
        CMAKE_ARGS -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD} -DCMAKE_C_COMPILER='${CMAKE_C_COMPILER}' -DCMAKE_CXX_COMPILER='${CMAKE_CXX_COMPILER}' -DCMAKE_SYSTEM_PROCESSOR=${DCMAKE_SYSTEM_PROCESSOR}
          -DCMAKE_ASM_FLAGS='${CMAKE_ASM_FLAGS}' -DCMAKE_LINK_FLAGS='${CMAKE_LINK_FLAGS}'
)

add_executable(cereal cereal.cpp ${SOURCE_FILES})
add_dependencies(cereal cereal_dep)
target_include_directories(cereal PUBLIC ${cereal_INCLUDE})
target_link_libraries(cereal PRIVATE Testing::core)
add_test(NAME test_cereal COMMAND cereal)