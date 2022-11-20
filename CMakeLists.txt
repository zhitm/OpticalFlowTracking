cmake_minimum_required(VERSION 3.23)
project(OpticalFlowTracking)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(OpticalFlowTracking main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
