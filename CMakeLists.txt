CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(PROJ_NAME CPM)
PROJECT (${PROJ_NAME})

ADD_DEFINITIONS(-DWITH_SSE)

find_package( OpenCV REQUIRED )
find_package( Eigen3 REQUIRED )

if(NOT DEFINED EIGEN3_INCLUDE_DIR)
  find_path(EIGEN3_INCLUDE_DIR eigen3)
endif(NOT DEFINED EIGEN3_INCLUDE_DIR)

include_directories(
    include
    cv_ext/include
    ${EIGEN3_INCLUDE_DIR}
)

#add_subdirectory(cv_ext)

add_executable(${PROJ_NAME} main.cpp CPM.cpp)
target_link_libraries(${PROJ_NAME} ${OpenCV_LIBS} )

add_executable(${PROJ_NAME}_plot plot.cpp CPM.cpp)
target_link_libraries(${PROJ_NAME}_plot ${OpenCV_LIBS})