#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include "MyTracker.h"

using namespace cv;
using namespace std;

cv::Rect2d box;

//Point2f getMean(vector<Point2f> &vec) {
//    float sumX = 0;
//    float sumY = 0;
//    for (const Point2f &p: vec) {
//        sumX += p.x;
//        sumY += p.y;
//    }
//    float meanX = sumX / vec.size();
//    float meanY = sumY / vec.size();
//    return {meanX, meanY};
//
//}
//
//Point2i getBoxMotion(vector<Point2f> &oldFeatures, vector<Point2f> &newFeatures) {
//    Point2f oldMean = getMean(oldFeatures);
//    Point2f newMean = getMean(newFeatures);
//    return newMean - oldMean;
//}
//
//cv::Rect2d getIntersection(Mat img, Rect2d box) {
//    Point2d leftCorner = {max(0.0, box.x - box.width / 2), max(0.0, box.y - box.width / 2)};
//    Point2d rightCorner = {min(double(img.rows), box.x + box.width / 2), min(double(img.cols), box.y + box.width / 2)};
//    return Rect2d(leftCorner, Size(rightCorner.x - leftCorner.x, rightCorner.y - leftCorner.y));
//}
//
//void updateBoxPosition(vector<Point2f> &oldFeatures, vector<Point2f> &newFeatures) {
//    Point2f boxMotion = getBoxMotion(oldFeatures, newFeatures);
//    box.x += boxMotion.x;
//    box.y += boxMotion.y;
//}
//
//vector<Point2f>
//selectGoodFeaturesAndDrawTracks(vector<Point2f> &oldFeatures, vector<Point2f> &newFeatures, vector<uchar> &status,
//                                Mat &mask, Mat &frame, vector<Scalar> &colors) {
//    vector<Point2f> good_new;
//    for (uint i = 0; i < oldFeatures.size(); i++) {
//        // Select good points
//        if (status[i] == 1) {
//            good_new.push_back(newFeatures[i]);
//            // draw the tracks
//            Point2f realP1 = Point2f(newFeatures[i].x + box.x, newFeatures[i].y + box.y);
//            Point2f realP0 = Point2f(oldFeatures[i].x + box.x, oldFeatures[i].y + box.y);
//
//            line(mask, realP1, realP0, colors[i], 2);
//            circle(frame, realP1, 5, colors[i], -1);
//        }
//    }
//    return good_new;
//}
//
//vector<Scalar> getRandomColors(int count) {
//    vector<Scalar> colors = vector<Scalar>();
//    RNG rng;
//    for (int i = 0; i < 100; i++) {
//        int r = rng.uniform(0, 256);
//        int g = rng.uniform(0, 256);
//        int b = rng.uniform(0, 256);
//        colors.push_back(Scalar(r, g, b));
//    }
//    return colors;
//}

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Incorrect args" << endl;
        return 0;
    }
    VideoCapture capture(argv[1]);
    if (!capture.isOpened()) {
        //error in opening the video input
        cerr << "Unable to open file!" << endl;
        return 0;
    }
    namedWindow("Frame", WINDOW_AUTOSIZE);

    Mat frame;
    capture >> frame;
    box = selectROI("Frame", frame);
    MyTracker tracker = MyTracker();
    cout<<box<<endl;

    tracker.startTracking(capture, box);
    box = tracker.getNextPedestrianPosition();
    while (!frame.empty()) {
        box = tracker.getNextPedestrianPosition();
        cout<<box<<endl;
        capture>>frame;
        rectangle(frame, box, cv::Scalar(0, 255, 0));
        imshow("Frame", frame);

        waitKey(30);
    }

//    Rect2d intersection = pedestrianBox;
//    cout<<intersection<<endl;
//    int featuresCount = 25;
//    // Create some random colors
//    vector<Scalar> colors = getRandomColors(featuresCount);
//
//    Mat old_frame, old_gray;
//    vector<Point2f> oldFeatures, newFeatures;
//    // Take first frame and find corners in it
//    capture >> old_frame;
//    cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
//    goodFeaturesToTrack(old_gray(box), oldFeatures, featuresCount, 0.3, 7, Mat(), 7, false, 0.04);
//    // Create a mask image for drawing purposes
//    Mat mask = Mat::zeros(old_frame.size(), old_frame.type());
//    while (!frame.empty()) {
//        Mat frame_gray;
//        if (frame.empty())
//            break;
//        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
//        // calculate optical flow
//        vector<uchar> status;
//        vector<float> err;
//        TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
//        calcOpticalFlowPyrLK(old_gray(box), frame_gray(box), oldFeatures, newFeatures, status, err, Size(15, 15), 2,
//                             criteria);
//        vector<Point2f> good_new = selectGoodFeaturesAndDrawTracks(oldFeatures, newFeatures, status, mask, frame,
//                                                                   colors);
//
//        updateBoxPosition(oldFeatures, newFeatures);
//        rectangle(frame, box, cv::Scalar(0, 255, 0));
//
//        Mat img;
//        add(frame, mask, img);
//        imshow("Frame", img);
//        int keyboard = waitKey(30);
//        if (keyboard == 'q' || keyboard == 27)
//            break;
//        // Now update the previous frame and previous points
//        old_gray = frame_gray.clone();
//        oldFeatures = good_new;
//        if (oldFeatures.size() < 5) {
//            goodFeaturesToTrack(frame_gray(box), oldFeatures, featuresCount, 0.3, 7, Mat(), 7, false, 0.04);
//        }
//        cout << good_new.size() << endl;
//        for (auto p: good_new) {
//            cout << p << " ";
//        }
//        cout << endl;
//        capture >> frame;
//    }
}