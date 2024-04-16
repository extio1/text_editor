# cmake_minimum_required(VERSION 3.1)

# ## Locate GTest
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})  # Var managed by CMake

# ## Add GTest required libraries to linker
# link_libraries(${GTEST_LIBRARIES} gtest_main pthread)

# ## Set c++ 11 std
# set(CMAKE_CXX_STANDARD 11)

# ## Include our source directories
# set(CMAKE_INCLUDE_CURRENT_DIR True)

# ## Set gcov flags
# set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
# set(CMAKE_EXE_LINKER_FLAGS "-lgcov")

# ## Define executables for each test suite
# set(SIMPLE "runSimpleTests")
# add_executable(${SIMPLE} "simple_tests.cpp" "../src/vector.cpp")


cmake_minimum_required(VERSION 3.1)

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
