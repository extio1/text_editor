cmake_minimum_required(VERSION 3.14)
project(vector)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
#   GIT_REPOSITORY https://github.com/google/googletest
#   GIT_TAG        v1.8.x 
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


file(GLOB sources CONFIGURE_DEPENDS "src/*")
file(GLOB headers CONFIGURE_DEPENDS "include/*")
file(GLOB tests CONFIGURE_DEPENDS "test/*")

enable_testing()

add_library(vector_lib SHARED ${sources} ${headers})
target_compile_options(vector_lib PRIVATE -Wall -Wextra -Wconversion -pedantic -g)

add_executable(vector "main.cpp")
target_link_libraries(vector vector_lib)
target_compile_options(vector PRIVATE -Wall -Wextra -Wconversion -pedantic -g)

add_executable(vector_test ${tests})
target_link_libraries(vector_test vector_lib)
target_link_libraries(vector_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(vector_test)
