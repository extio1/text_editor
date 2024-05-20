set(target model_test)

set(CTEST_PROGRESS_OUTPUT)
set(CTEST_OUTPUT_ON_FAILURE)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(${target} text_editor_tests.cpp)
target_link_libraries(${target} PRIVATE document point compositor GTest::gtest_main)
add_test(NAME model_test COMMAND model_test)
