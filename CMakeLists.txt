cmake_minimum_required(VERSION 3.14)
project(test_editor)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "src/*")
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "include/*")
file(GLOB_RECURSE tests CONFIGURE_DEPENDS "test/*")

add_library(text_editor_lib SHARED ${sources} ${headers})
target_include_directories(text_editor_lib PUBLIC include)
target_compile_options(text_editor_lib PRIVATE -Wall -Wextra -Wconversion -pedantic -g)

add_executable(text_editor "main.cpp")
target_include_directories(text_editor PUBLIC include)
target_link_libraries(text_editor text_editor_lib)
target_compile_options(text_editor PRIVATE -Wall -Wextra -Wconversion -pedantic -g)

add_executable(text_editor_test ${tests})
target_include_directories(text_editor_test PUBLIC include)
target_link_libraries(text_editor_test text_editor_lib GTest::gtest_main)
target_compile_options(text_editor_test PRIVATE -Wall -Wextra -Wconversion -pedantic -g)

include(GoogleTest)
gtest_discover_tests(text_editor_test)