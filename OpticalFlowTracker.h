
#ifndef OPTICALFLOWTRACKING_OPTICALFLOWTRACKER_H
#define OPTICALFLOWTRACKING_OPTICALFLOWTRACKER_H


#include "Tracker.h"

class OpticalFlowTracker : public Tracker {
    cv::Mat oldFrame;
    cv::Mat oldGray;
    std::vector<cv::Point2f> oldFeatures, newFeatures;
    int featuresCount = 25;
    void updateBoxPosition();
    cv::Point2i getBoxMotion();
    cv::VideoCapture capture;
    cv::Rect2d pedestrianBox;

    std::vector<cv::Point2f> selectGoodFeatures(std::vector<uchar> &status, cv::Mat &frame);

public:
    OpticalFlowTracker();
    void startTracking(cv::VideoCapture capture, cv::Rect2d pedestrian);
    cv::Rect2d getNextPedestrianPosition();

};


#endif //OPTICALFLOWTRACKING_OPTICALFLOWTRACKER_H
