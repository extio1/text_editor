cmake_minimum_required(VERSION 3.14)
project(text_editor_project)

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

set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(test_dir ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_subdirectory(src)


set(target text_editor)
set(target_test text_editor_test)

add_executable(${target} main.cpp)
target_include_directories(${target} PUBLIC ${include_dir})

add_executable(${target_test} ${test_dir}/text_editor_tests.cpp)
target_include_directories(${target_test} PUBLIC ${include_dir})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wconversion -pedantic -g)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${target_test} PRIVATE -Wall -Wextra -Wconversion -pedantic -g)
endif()

target_link_libraries(${target} document point)
target_link_libraries(${target_test} document point GTest::gtest_main)