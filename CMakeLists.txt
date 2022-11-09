# Generate main files

cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 17)

# Project name
project(STIR_TOOL)

# add executable
add_subdirectory(src/)


# add the installation directory.
install(TARGETS ${PROJECT_NAME})