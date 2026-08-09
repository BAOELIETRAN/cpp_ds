# root CMake file
cmake_minimum_required(VERSION 3.14)

project(CPP_DS LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# create testing infrastructure at root level
# ctest is enabled at parent level --> subdirs can register tests 
# that will be visible at parent level
# ctest - test runner of CMake
enable_testing()

# go process vector/CMakeLists.txt
# build from root: ctest is already enabled at parent level
# --> enable_testing() in child CMake file will be ignored
# build directly from subdir (without root): cmake reads 
# child CMake file --> create test infra at that child level --> root will not know
# build from root without root enable_testing(): cmake will
# create test infra at child level --> tests are registered at that level
# --> root does not know about tests
# if we have other projects in cpp_ds, this parent cmakelists will help us build all the projects
# and run all the tests
add_subdirectory(vector)
add_subdirectory(linked_list)
add_subdirectory(stack)
add_subdirectory(queue)
add_subdirectory(binary_search_tree)
add_subdirectory(priority_queue)
add_subdirectory(doubly_linked_list)
add_subdirectory(hash_map)
add_subdirectory(trie)
add_subdirectory(revision/vector)


# a few helpful commands:
# ====================================================================
# cmake -S . -B build -G "MinGW Makefiles"
# cmake -B .\build - read your CMakeLists.txt and generate build files in the ./build directory
# after running cmake -B .\build, here is what happened:
# cpp_ds/
# └── build/                           ← Created by cmake -B build
#     ├── CMakeCache.txt               ← CMake configuration cache
#     ├── CMakeFiles/                  ← CMake internal files
#     ├── Makefile                     ← THE BUILD FILE (on Linux/Mac)
#     ├── cpp_ds.sln                   ← THE BUILD FILE (on Windows with Visual Studio)
#     ├── CTestTestfile.cmake          ← Test registry (root level)
#     ├── _deps/                       ← Downloaded dependencies (GoogleTest)
#     │   └── googletest-build/
# ====================================================================
#      (dir to search for build files - ./build)
#                   |
# cmake --build .\build\ - read the build files (eg. Makefile) and compile your code
#           |
# (tell CMake to build the project)
# ====================================================================
# ctest --test-dir .\build\ - find and run all registered tests
# (look for all tests in the ./build directory)
# ctest - a tool to run tests and report results
# to run a single test - ctest --test-dir .\build\ -R (run tests matching this regex) + "regex matching of the test"
# Ex: ctest --test-dir .\build\ -R "AddingTest" --> run test suite "AddingTest"
# Ex: ctest --test-dir .\build\ -R "HandleNegativeInt" --> run test "HandleNegativeInt"
