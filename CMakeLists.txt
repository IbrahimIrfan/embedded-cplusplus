cmake_minimum_required(VERSION 3.1)
project(EmbeddedCplusplus)
enable_testing()

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

set(GTEST_INCLUDE_DIR ${gtest_SOURCE_DIR}/include)
set(WLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/wlib)

add_subdirectory(include/gtest-1.8.0)
add_subdirectory(lib/wlib)
add_subdirectory(examples)
add_subdirectory(tests)
add_test(NAME EmbeddedCplusplusTests COMMAND tests)
