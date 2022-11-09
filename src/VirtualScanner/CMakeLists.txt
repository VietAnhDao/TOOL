add_library(VirtualScanner "")

target_sources(VirtualScanner
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/VirtualScanner.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/VirtualScanner.h
  )
target_include_directories(VirtualScanner
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )