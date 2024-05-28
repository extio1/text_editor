cmake_minimum_required(VERSION 3.14)
project(text_editor_project)

set(target text_editor)
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(test_dir ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_subdirectory(src)
enable_testing()
add_subdirectory(test)

add_executable(${target} main.cpp)
message(${include_dir})
target_include_directories(${target} PUBLIC ${include_dir})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wconversion -pedantic -g)
endif()

target_link_libraries(${target} executor document point compositor)
