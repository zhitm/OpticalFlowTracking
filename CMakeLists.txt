cmake_minimum_required(VERSION 3.23)
project(PedestrianTracking)

set(CMAKE_CXX_STANDARD 17)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(${PROJECT_NAME} main.cpp MyTracker.cpp MyTracker.h trackers/Tracker.cpp trackers/Tracker.h trackers/OpticalFlowTracker.cpp trackers/OpticalFlowTracker.h trackers/KCFTracker.cpp trackers/KCFTracker.h)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
