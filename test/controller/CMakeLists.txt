add_executable(circular_buffer_test circular_buffer_tests.cpp)
target_include_directories(circular_buffer_test PRIVATE ${include_dir})
target_link_libraries(circular_buffer_test PRIVATE GTest::gtest_main)
add_test(NAME circular_buffer_test COMMAND circular_buffer_test)

add_executable(executor_test executor_tests.cpp)
target_link_libraries(executor_test PRIVATE executor document compositor point GTest::gtest_main GTest::gmock_main)
add_test(NAME executor_test COMMAND executor_test)

set_tests_properties(executor_test PROPERTIES DEPENDS circular_buffer_test)
