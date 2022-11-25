#ifndef OPTICALFLOWTRACKING_KCFTRACKER_H
#define OPTICALFLOWTRACKING_KCFTRACKER_H


#include <opencv2/tracking.hpp>
#include "Tracker.h"

class KCFTracker: public Tracker {
    cv::VideoCapture capture;
    cv::Rect2i pedestrianBox;
    cv::Ptr<cv::TrackerKCF> tracker;
public:
    KCFTracker();
    void startTracking(cv::VideoCapture capture, cv::Rect2d pedestrian) override;
    cv::Rect2d getNextPedestrianPosition() override;
};


#endif //OPTICALFLOWTRACKING_KCFTRACKER_H
