set(target model_test)

add_executable(${target} text_editor_tests.cpp)
target_link_libraries(${target} PRIVATE document point compositor GTest::gtest_main)
add_test(NAME model_test COMMAND model_test)
