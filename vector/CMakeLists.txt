# A CMake file describes how a C++ project should be built, 
# and CMake generates platform-specific build files that call the compiler.

# cmake version >= 3.14 (must)
cmake_minimum_required(VERSION 3.14)

# project declaration
# name: MY_VECTOR
# language: cxx - c++
# --> allow cmake to find the correct compiler
project(MY_VECTOR LANGUAGES CXX)

# set the project standard
# need to be 20
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

# enable CMake's testing system (CTest)
# --> allowing user to register project's tests and run them with ctest  
# cmake does not look up for test files 
enable_testing()

# take vector.cpp and compile it into a reusable library "my_vector_lib"
# --> link it whenever user needs
# reminder: preprocessor only copies source code of header file to a code file
# and the source code files are compiled independently
# the google test program will be the program, and our code will be the library
add_library(my_vector_lib
    src/vector.cpp
)

# Any files that use "my_vector_lib" is allowed to use "#include "vector.h""
# simply saying, when a file want to use "my_vector_lib" is in a different folder
# from the vector.h file, we need this to specify that program to compile with 
# -I path/to/the/header/file
target_include_directories(my_vector_lib PUBLIC src)

# create an .exe file "my_vector_tests" from test_vector.cpp
add_executable(my_vector_tests
    tests/test_vector.cpp
)

# tell the linker: here is the binary code for functions you see in the exe file "my_vector_tests"
target_link_libraries(my_vector_tests
    my_vector_lib
    GTest::gtest_main
)

# this helps CMake understand google test
include(GoogleTest)

# run the test file
gtest_discover_tests(my_vector_tests)
