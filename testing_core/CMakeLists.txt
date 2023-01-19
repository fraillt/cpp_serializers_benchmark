# OpenCV
find_package(OpenCV REQUIRED)

add_library(testingcore SHARED test.cpp types.cpp)
#add_library(Testing::core ALIAS testingcore)

target_include_directories(testingcore
        PUBLIC ./
        ${OpenCV_INCLUDE_DIRS}
        )
target_link_libraries(testingcore
        PUBLIC
        ${OpenCV_LIBS}
        )

target_compile_features(testingcore PUBLIC cxx_auto_type)