//
// Created by maria on 23.11.22.
//

#ifndef OPTICALFLOWTRACKING_MYTRACKER_H
#define OPTICALFLOWTRACKING_MYTRACKER_H

#include <opencv2/videoio.hpp>
#include "Tracker.h"

class MyTracker: Tracker {
    cv::Mat currentFrame;
public:
    std::vector<Tracker> trackers;
    MyTracker();
    void startTracking(cv::VideoCapture capture, cv::Rect2d pedestrian) override;
    cv::Rect2d getNextPedestrianPosition();
    cv::VideoCapture capture;

};

#endif //OPTICALFLOWTRACKING_MYTRACKER_H
