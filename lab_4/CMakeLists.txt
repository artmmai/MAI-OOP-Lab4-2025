cmake_minimum_required(VERSION 3.10)
project(MAI-OOP-LAB4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

# Основная библиотека (все заголовки с шаблонной реализацией)
add_library(lab4_lib INTERFACE)
target_include_directories(lab4_lib INTERFACE include)

# Исполняемый файл (меню)
add_executable(lab4_exe main.cpp)
target_link_libraries(lab4_exe lab4_lib)

# Тесты
enable_testing()
add_executable(tests test/test04.cpp)
target_link_libraries(tests lab4_lib gtest_main)

add_test(NAME Lab4-Tests COMMAND tests)
