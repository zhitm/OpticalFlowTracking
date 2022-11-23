cmake_minimum_required(VERSION 3.23)
project(OpticalFlowTracking)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(OpticalFlowTracking main.cpp MyTracker.cpp MyTracker.h Tracker.cpp Tracker.h OpticalFlowTracker.cpp OpticalFlowTracker.h)
add_executable(Tracker tracker.cpp OpticalFlowTracker.cpp OpticalFlowTracker.h)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(Tracker ${OpenCV_LIBS})
