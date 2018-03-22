
add_library(testingcore STATIC test.cpp types.cpp)
add_library(Testing::core ALIAS testingcore)

target_include_directories(testingcore PUBLIC ./)
target_compile_features(testingcore PUBLIC cxx_auto_type)