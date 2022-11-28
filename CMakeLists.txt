# Generate main files
cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
# Project name
project(TOOL)

# subdirectory
add_subdirectory(external/)
add_subdirectory(src/)
add_subdirectory(tests/)