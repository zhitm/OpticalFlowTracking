//
// Created by maria on 27.11.22.
//

#include <iostream>
#include "CSRTTracker.h"

void CSRTTracker::startTracking(std::string path, cv::Rect2d pedestrian) {
    capture = cv::VideoCapture(path);
    pedestrianBox = pedestrian;
    tracker = cv::TrackerCSRT::create();
    cv::Mat frame;
    capture>>frame;
    tracker->init(frame, pedestrianBox);
}

CSRTTracker::CSRTTracker() = default;

cv::Rect2d CSRTTracker::getNextPedestrianPosition() {
    cv::Mat frame;
    capture>>frame;
    if (!tracker->update(frame, pedestrianBox)){
        std::cout << "failed csrt tracking"<< std::endl;
    }
    return pedestrianBox;
}
