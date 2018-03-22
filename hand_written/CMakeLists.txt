add_executable(hand_written hand_written.cpp )
target_link_libraries(hand_written PRIVATE Testing::core)
add_test(NAME test_hand_written COMMAND hand_written)

add_executable(hand_written_no_checking hand_written_unsafe.cpp)
target_link_libraries(hand_written_no_checking PRIVATE Testing::core)
add_test(NAME test_hand_written_no_checking COMMAND hand_written_no_checking)
