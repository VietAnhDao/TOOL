# Generate main files
cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 17)
# Project name
project(TOOL)
add_subdirectory(src/)
add_subdirectory(external/)
add_subdirectory(tests/)
#install(TARGETS ${PROJECT_NAME})