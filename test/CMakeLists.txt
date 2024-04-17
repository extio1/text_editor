cmake_minimum_required(VERSION 3.10)
project(vector)

# Установка пути к заголовочным файлам Google Test
include_directories(gtest/googletest/googletest/include)

# Установка пути к библиотеке Google Test
link_directories(gtest/googletest/build/lib)

# Добавление исполняемого файла для тестов
set(SIMPLE "runSimpleTests")
add_executable(${SIMPLE} "simple_tests.cpp" "../src/vector.cpp")

# Добавление библиотеки Google Test к вашим тестам
target_link_libraries(${SIMPLE} gtest gtest_main pthread)

# Установка стандарта C++11
set(CMAKE_CXX_STANDARD 11)

# Включение текущего каталога
set(CMAKE_INCLUDE_CURRENT_DIR True)

# Установка флагов gcov
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov")
