#include "MyTracker.h"
#include "trackers/OpticalFlowTracker.h"
#include "trackers/KCFTracker.h"

MyTracker::MyTracker() {
    Tracker *opticalFlowTracker = new OpticalFlowTracker();
    Tracker *kcfTracker = new KCFTracker();
    trackers.push_back(opticalFlowTracker);
    trackers.push_back(kcfTracker);
}

cv::Rect2d MyTracker::getNextPedestrianPosition() {
    return trackers[1]->getNextPedestrianPosition();
}

void MyTracker::startTracking(cv::VideoCapture videoCapture, cv::Rect2d pedestrian) {
    for (auto tracker: trackers) {
        tracker->startTracking(videoCapture, pedestrian);
    }
}
