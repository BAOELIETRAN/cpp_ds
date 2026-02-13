# A CMake file describes how a C++ project should be built.
# == It generates scripts for other build automation tools.
# CMake generates build files (e.g., Makefiles, Ninja files, ...) - Makefiles build project.

# cmake version >= 3.14 (must)
# this project needs CMAKE version >= 3.14
cmake_minimum_required(VERSION 3.14)

# project declaration
# name: MY_BST
# language: cxx - c++
# --> allow cmake to find a C++ compiler and set up C++ build rules
project(MY_BST LANGUAGES CXX)

# set the project standard
# compile everything with C++ 20 (must)
# if our compiler doesn't support C++ 20 --> fail (instead of CMake silently fallback to C++ 17)
set(CMAKE_CXX_STANDARD 20)
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

# take bst.cpp and compile it into a reusable library "my_bst_lib"
# --> link it whenever user needs
# reminder: preprocessor only copies source code of header file to a code file
# and the source code files are compiled independently
# the google test program will be the program, and our code will be the library
add_library(my_bst_lib
    src/bst.cpp
)

# Any files that use "my_bst_lib" is allowed to use "#include "bst.h""
# simply saying, when a file want to use "my_bst_lib" is in a different folder
# from the bst.h file, we need this to specify that program to compile with 
# -I path/to/the/header/file
target_include_directories(my_bst_lib PUBLIC src)

# create an .exe file "my_bst_tests" from test_bst.cpp
add_executable(my_bst_tests
    tests/test_bst.cpp
)

# tell the linker: here is the binary code for functions you see in the exe file "my_bst_tests"
target_link_libraries(my_bst_tests
    my_bst_lib
    GTest::gtest_main
)

# load built-in Google Test CMake module, 
# which provides helper functions (e.g., gtest_discover_tests)

include(GoogleTest)

# finds, registers (with CTest), and runs Google Test tests defined in my_bst_tests
gtest_discover_tests(my_bst_tests)

# the test program (test_bst.cpp) is the main program, and it is linked
# with the bst.cpp program and google test.
# --> we need to tell the test bst program where is the header file when it is linked with the bst.cpp program.
# (linking is for compiled code, but I use .cpp here for simplicity)
