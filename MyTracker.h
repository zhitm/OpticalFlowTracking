#ifndef OPTICALFLOWTRACKING_MYTRACKER_H
#define OPTICALFLOWTRACKING_MYTRACKER_H

#include <opencv2/videoio.hpp>
#include "trackers/Tracker.h"

class MyTracker : Tracker {
    cv::Mat currentFrame;
public:
    std::vector<Tracker *> trackers;

    MyTracker();

    void startTracking(cv::VideoCapture videoCapture, cv::Rect2d pedestrian) override;

    cv::Rect2d getNextPedestrianPosition() override;

    cv::VideoCapture capture;

};

#endif //OPTICALFLOWTRACKING_MYTRACKER_H
