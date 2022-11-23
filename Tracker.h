//
// Created by maria on 23.11.22.
//

#ifndef OPTICALFLOWTRACKING_TRACKER_H
#define OPTICALFLOWTRACKING_TRACKER_H

#include <opencv2/videoio.hpp>

class Tracker {
public:
    Tracker();
    virtual void startTracking(cv::VideoCapture capture, cv::Rect2d pedestrian);
    virtual cv::Rect2d getNextPedestrianPosition();

};

#endif //OPTICALFLOWTRACKING_TRACKER_H
