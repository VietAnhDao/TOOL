#add_executable(${PROJECT_NAME} PrintCrystalMap.cpp)
#add_subdirectory(include)
#target_link_libraries(${PROJECT_NAME}
#  PRIVATE
#    include
#  )



# get all executable from source folder
file(GLOB SOURCE_FILES source/*.c source/*.cpp source/*.cxx)
# loop through all executable and build each one with each name space
foreach(SOURCE_PATH ${SOURCE_FILES})
  get_filename_component(EXECUTABLE_NAME ${SOURCE_PATH} NAME_WE)
  add_executable(${EXECUTABLE_NAME} ${SOURCE_PATH})
  # Add include directory to each executable
  add_subdirectory(include)
  # link all the library in the include to executable
  target_link_libraries(${EXECUTABLE_NAME}
    PUBLIC
      include
    )
  install(TARGETS ${EXECUTABLE_NAME})
  endforeach(SOURCE_PATH ${SOURCE_FILES})
