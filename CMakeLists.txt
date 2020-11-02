cmake_minimum_required(VERSION 3.9)

project(tester)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(googletest)

include_directories(googletest/googletest/include)


add_executable(tester tests.cpp)

target_link_libraries(tester gtest gtest_main)
