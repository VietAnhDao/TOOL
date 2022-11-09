add_executable(${PROJECT_NAME} main.cpp)
  
add_subdirectory(VirtualScanner)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    VirtualScanner
  )
