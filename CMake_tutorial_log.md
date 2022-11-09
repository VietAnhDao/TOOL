# Generating a starting file for cmake.
Starting file.
- File must be named "CMakeLists.txt" exactly.
- must contain "cmake_minimum_required(VERSION 3.13.4)"

# Subdirectory
1. Add this to CMakeLists.txt at the root directory:
    - "add_library(some_target main.cpp)"
    - "add_subdirectory(sub_dir)"
2. Add this to CMakeLists.txt at the sub directory:
    - "target_sources(some_target PRIVATE more_cool_stuff.cpp)"