# ======================== FINDING PACKAGE =============================
FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(Armadillo REQUIRED) # used for linear algebra
FIND_PACKAGE(sipm REQUIRED PATHS ${CMAKE_SOURCE_DIR}/external)
FIND_PACKAGE(ROOT REQUIRED)
# DEBUG 
message(STATUS "Armadillo: found=${ARMADILLO_FOUND}, include_dirs=${ARMADILLO_INCLUDE_DIRS}, lib=${ARMADILLO_LIBRARIES}, version=${ARMADILLO_VERSION}")
message(STATUS "Boost: found=${Boost_FOUND}, include_dirs=${Boost_INCLUDE_DIRS}, lib=${Boost_LIBRARY}, version=${Boost_VERSION}")
message(STATUS "sipm: found=${sipm_FOUND}, include_dirs=${sipm_INCLUDE_DIRS}, lib=${sipm_LIBRARY}, version=${sipm_VERSION}")
message(STATUS "root: found=${ROOT_FOUND}, include_dirs=${ROOT_INCLUDE_DIRS}, lib=${ROOT_LIBRARIES}, version=${ROOT_VERSION}")
# ======================== ADD INCLUDE DIR =============================
include_directories(${ARMADILLO_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_INCLUDE_DIRS}) # custom user defined include dir
include_directories(${ROOT_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/external/include/sipm) # external folder include.
include_directories(${CMAKE_SOURCE_DIR}/external/include)
# ======================== FIND & COMPILE ALL EXECUTABLE ===============
# get all executable from source folder
file(GLOB SOURCE_FILES source/*.c source/*.cpp source/*.cxx)
# loop through all executable and build each one with each name space
foreach(SOURCE_PATH ${SOURCE_FILES})
  get_filename_component(EXECUTABLE_NAME ${SOURCE_PATH} NAME_WE)
  add_executable(${EXECUTABLE_NAME} ${SOURCE_PATH})
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
      ${ROOT_LIBRARIES}
    )
  install(TARGETS ${EXECUTABLE_NAME})
endforeach(SOURCE_PATH ${SOURCE_FILES})
