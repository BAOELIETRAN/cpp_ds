# A CMake file describes how a C++ project should be built.

cmake_minimum_required(VERSION 3.14)

project(MY_NEW_HASH_MAP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(my_new_hash_map_lib
    src/hash_map.cpp
)

target_include_directories(my_new_hash_map_lib PUBLIC src)

add_executable(my_new_hash_map_tests
    tests/test_hash_map.cpp
)

target_link_libraries(my_new_hash_map_tests
    my_new_hash_map_lib
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(my_new_hash_map_tests)
