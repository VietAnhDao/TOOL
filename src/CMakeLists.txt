#add_executable(${PROJECT_NAME} PrintCrystalMap.cpp)
#add_subdirectory(include)
#target_link_libraries(${PROJECT_NAME}
#  PRIVATE
#    include
#  )


# ======================== FINDING PACKAGE =============================
#FIND_PACKAGE(Boost)
#find_package(BLAS)
#find_package(LAPACK)
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
# ======================== FIND & COMPILE ALL EXECUTABLE ===============
# get all executable from source folder
file(GLOB SOURCE_FILES source/*.c source/*.cpp source/*.cxx)
# loop through all executable and build each one with each name space
foreach(SOURCE_PATH ${SOURCE_FILES})
  get_filename_component(EXECUTABLE_NAME ${SOURCE_PATH} NAME_WE)
  add_executable(${EXECUTABLE_NAME} ${SOURCE_PATH})
  # ===================== LINK ALL EXTERNAL PACKAGE ===================
  #IF (Boost_FOUND)
  #  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
  #  ADD_DEFINITIONS( "-DHAS_BOOST" )
  #ENDIF()
  #if(LAPACK_FOUND AND BLAS_FOUND)
  #  set(lapackblas_libraries "${BLAS_LIBRARIES} ${LAPACK_LIBRARIES}")
  #endif()
  # ====================== LINK INTERNAL PACKAGE =======================
  add_subdirectory(include)
  # link all the library in the include to executable
  target_link_libraries(${EXECUTABLE_NAME}
    PUBLIC
      # INTERNAL LIB
      include
      # EXTERNAL LIB
      #${lapackblas_libraries}
      ${ARMADILLO_LIBRARIES}
    )
  install(TARGETS ${EXECUTABLE_NAME})
endforeach(SOURCE_PATH ${SOURCE_FILES})
