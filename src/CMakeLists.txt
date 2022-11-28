#add_executable(${PROJECT_NAME} PrintCrystalMap.cpp)
#add_subdirectory(include)
#target_link_libraries(${PROJECT_NAME}
#  PRIVATE
#    include
#  )


# ======================== FINDING PACKAGE =============================
#find_package(BLAS)
#find_package(LAPACK)
FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(Armadillo REQUIRED)
FIND_PACKAGE(sipm REQUIRED)
# DEBUG 
message(STATUS "Armadillo: found=${ARMADILLO_FOUND}, include_dirs=${ARMADILLO_INCLUDE_DIRS}, lib=${ARMADILLO_LIBRARIES}, version=${ARMADILLO_VERSION}")
message(STATUS "Boost: found=${Boost_FOUND}, include_dirs=${Boost_INCLUDE_DIRS}, lib=${Boost_LIBRARY}, version=${Boost_VERSION}")
message(STATUS "sipm: found=${sipm_FOUND}, include_dirs=${sipm_INCLUDE_DIRS}, lib=${sipm_LIBRARY}, version=${sipm_VERSION}")
# ======================== ADD INCLUDE DIR =============================
include_directories(${ARMADILLO_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/external/include/sipm)
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
      ${BOOST_LIBRARIES}
    )
  install(TARGETS ${EXECUTABLE_NAME})
endforeach(SOURCE_PATH ${SOURCE_FILES})
