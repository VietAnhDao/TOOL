add_library(include "")

# cmake find the libary
target_sources(include
  PRIVATE 
  ${CMAKE_CURRENT_LIST_DIR}/VirtualScanner.cpp
  ${CMAKE_CURRENT_LIST_DIR}/SiPM.cpp
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/VirtualScanner.h
  ${CMAKE_CURRENT_LIST_DIR}/extend_armadillo.h
  ${CMAKE_CURRENT_LIST_DIR}/extend_boost.h
  ${CMAKE_CURRENT_LIST_DIR}/SiPM.h
)

# This is required for the executable to find the lib
target_include_directories(include
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)