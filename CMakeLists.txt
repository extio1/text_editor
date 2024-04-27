# cmake_minimum_required(VERSION 3.14)
# project(vector)

# # GoogleTest requires at least C++14
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include(FetchContent)
# FetchContent_Declare(
#     googletest
# #   GIT_REPOSITORY https://github.com/google/googletest
# #   GIT_TAG        v1.8.x 
#     URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )

# FetchContent_MakeAvailable(googletest)

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


# file(GLOB sources CONFIGURE_DEPENDS "src/*")
# file(GLOB headers CONFIGURE_DEPENDS "include/*")
# file(GLOB headers CONFIGURE_DEPENDS "include/glyphs/*")
# file(GLOB tests CONFIGURE_DEPENDS "test/*")

# enable_testing()

# # add_library(text_editor_lib SHARED ${sources} ${headers})
# add_library(text_editor_lib SHARED ${sources} ${headers} "src/glyphs/character.cpp" "src/glyphs/glyph.cpp")

# target_compile_options(text_editor_lib PRIVATE -Wall -Wextra -Wconversion -pedantic -g)

# add_executable(text_editor "src/main.cpp")
# target_link_libraries(text_editor text_editor_lib)
# target_compile_options(text_editor PRIVATE -Wall -Wextra -Wconversion -pedantic -g)

# # add_executable(vector_test ${tests})
# # target_link_libraries(vector_test vector_lib)
# # target_link_libraries(vector_test GTest::gtest_main)

# # include(GoogleTest)
# # gtest_discover_tests(vector_test)


cmake_minimum_required(VERSION 3.10)

project(text_editor)

# Устанавливаем пути к исходным и заголовочным файлам
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Собираем все заголовочные файлы
file(GLOB_RECURSE HEADERS ${INCLUDE_DIR}/*.h)

# Собираем все исходные файлы
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

# Создаем исполняемый файл text_editor из main.cpp
add_executable(text_editor ${SRC_DIR}/main.cpp ${SOURCES} ${HEADERS})

# Добавляем директории include для поиска заголовочных файлов
target_include_directories(text_editor PUBLIC ${INCLUDE_DIR})
