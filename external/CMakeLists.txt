# this should only be used if external project is small and can't be imported e.g. SimSiPM
include(ExternalProject)
ExternalProject_Add(SiPM
    GIT_REPOSITORY https://github.com/EdoPro98/SimSiPM
    GIT_TAG main
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/external
    UPDATE_DISCONNECTED True # prevent rebuilding of external project
)