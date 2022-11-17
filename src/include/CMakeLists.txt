add_library(include "")

# cmake find the libary
target_sources(include
  PRIVATE 
  ${CMAKE_CURRENT_LIST_DIR}/Vector3D.cpp
  ${CMAKE_CURRENT_LIST_DIR}/VirtualScanner.cpp
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Vector3D.h
  ${CMAKE_CURRENT_LIST_DIR}/VirtualScanner.h
)

# This is required for the executable to find the lib
target_include_directories(include
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)