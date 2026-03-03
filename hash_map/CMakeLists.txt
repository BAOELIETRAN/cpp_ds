# A CMake file describes how a C++ project should be built.
# == It generates scripts for other build automation tools.
# CMake generates build files (e.g., Makefiles, Ninja files, ...) - Makefiles build project.

# cmake version >= 3.14 (must)
# this project needs CMAKE version >= 3.14
cmake_minimum_required(VERSION 3.14)

# project declaration
# name: MY_HASH_MAP
# language: cxx - c++
# --> allow cmake to find a C++ compiler and set up C++ build rules
project(MY_HASH_MAP LANGUAGES CXX)

# set the project standard
# compile everything with C++ 20 (must)
# if our compiler doesn't support C++ 20 --> fail (instead of CMake silently fallback to C++ 17)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# turn on CMake's built-in dependency manager
include(FetchContent)
# declare an external dependency (google test)
# declare where to download it from
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# tells CMake to download GoogleTest (if needed) and build it with the project
# in the build file of the project --> there will be a build section for google test
FetchContent_MakeAvailable(googletest)

# activate testing infrastructure (CTest) at this level
# --> ctest makes testing easier!
enable_testing()

# take HASH_MAP.cpp and compile it into a reusable library "my_HASH_MAP_lib"
# --> link it whenever user needs
# reminder: preprocessor only copies source code of header file to a code file
# and the source code files are compiled independently
# the google test program will be the program, and our code will be the library
add_library(my_hash_map_lib
    src/hash_map.cpp
)

# Any files that use "my_HASH_MAP_lib" is allowed to use "#include "HASH_MAP.h""
# simply saying, when a file want to use "my_HASH_MAP_lib" is in a different folder
# from the HASH_MAP.h file, we need this to specify that program to compile with 
# -I path/to/the/header/file
target_include_directories(my_hash_map_lib PUBLIC src)

# create an .exe file "my_HASH_MAP_tests" from test_HASH_MAP.cpp
add_executable(my_hash_map_tests
    tests/test_hash_map.cpp
)

# tell the linker: here is the binary code for functions you see in the exe file "my_HASH_MAP_tests"
target_link_libraries(my_hash_map_tests
    my_hash_map_lib
    GTest::gtest_main
)

# load built-in Google Test CMake module, 
# which provides helper functions (e.g., gtest_discover_tests)

include(GoogleTest)

# finds, registers (with CTest), and runs Google Test tests defined in my_HASH_MAP_tests
gtest_discover_tests(my_hash_map_tests)

# the test program (test_HASH_MAP.cpp) is the main program, and it is linked
# with the HASH_MAP.cpp program and google test.
# --> we need to tell the test HASH_MAP program where is the header file when it is linked with the HASH_MAP.cpp program.
# (linking is for compiled code, but I use .cpp here for simplicity)
