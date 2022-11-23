//
// Created by maria on 23.11.22.
//

#include "MyTracker.h"
#include "OpticalFlowTracker.h"

MyTracker::MyTracker() {
    Tracker t = OpticalFlowTracker();
    trackers.push_back(t);
}

cv::Rect2d MyTracker::getNextPedestrianPosition() {
    return trackers[0].getNextPedestrianPosition();
}

void MyTracker::startTracking(cv::VideoCapture capture, cv::Rect2d pedestrian) {
    trackers[0].startTracking(capture, pedestrian);
}
