#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/types_c.h>

using namespace cv;
using namespace std;


bool gotBB = false;
bool drawing_box = false;
cv::Rect2d box;

void mouseHandler(int event, int x, int y, int flags, void *param) {
    switch (event) {
        case EVENT_MOUSEMOVE:
            if (drawing_box) {
                box.width = x - box.x;
                box.height = y - box.y;
            }
            break;
        case EVENT_LBUTTONDOWN:
            drawing_box = true;
            box = cv::Rect(x, y, 0, 0);
            break;
        case EVENT_LBUTTONUP:
            drawing_box = false;
            if (box.width < 0) {
                box.x += box.width;
                box.width *= -1;
            }
            if (box.height < 0) {
                box.y += box.height;
                box.height *= -1;
            }
            gotBB = true;
            break;
    }
}

void drawBox(cv::Mat &image, cv::Rect box, cv::Scalar color, int thick) {
    rectangle(image, cvPoint(box.x, box.y), cvPoint(box.x + box.width, box.y + box.height), color, thick);
}

Point2f getMean(vector<Point2f> &vec) {
    float sumX = 0;
    float sumY = 0;
    for (const Point2f &p: vec) {
        sumX += p.x;
        sumY += p.y;
    }
    float meanX = sumX / vec.size();
    float meanY = sumY / vec.size();
    return {meanX, meanY};

}

Point2i getBoxMotion(vector<Point2f> &oldFeatures, vector<Point2f> &newFeatures) {
    Point2f oldMean = getMean(oldFeatures);
    Point2f newMean = getMean(newFeatures);
    return newMean - oldMean;
}

void updateBoxPosition(vector<Point2f> &oldFeatures, vector<Point2f> &newFeatures) {
    Point2f boxMotion = getBoxMotion(oldFeatures, newFeatures);
    box.x += boxMotion.x;
    box.y += boxMotion.y;
}

vector<Point2f>
selectGoodFeaturesAndDrawTracks(vector<Point2f> &oldFeatures, vector<Point2f> &newFeatures, vector<uchar> &status,
                                Mat &mask, Mat &frame, vector<Scalar> &colors) {
    vector<Point2f> good_new;
    for (uint i = 0; i < oldFeatures.size(); i++) {
        // Select good points
        if (status[i] == 1) {
            good_new.push_back(newFeatures[i]);
            // draw the tracks
            Point2f realP1 = Point2f(newFeatures[i].x + box.x, newFeatures[i].y + box.y);
            Point2f realP0 = Point2f(oldFeatures[i].x + box.x, oldFeatures[i].y + box.y);

            line(mask, realP1, realP0, colors[i], 2);
            circle(frame, realP1, 5, colors[i], -1);
        }
    }
    return good_new;
}

vector<Scalar> getRandomColors(int count) {
    vector<Scalar> colors = vector<Scalar>();
    RNG rng;
    for (int i = 0; i < 100; i++) {
        int r = rng.uniform(0, 256);
        int g = rng.uniform(0, 256);
        int b = rng.uniform(0, 256);
        colors.push_back(Scalar(r, g, b));
    }
    return colors;
}

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

    // object selection
    namedWindow("Frame", WINDOW_AUTOSIZE);
    setMouseCallback("Frame", mouseHandler, NULL);
    cv::Mat frame;
    capture >> frame;
    cv::Mat temp;
    frame.copyTo(temp);
    while (!gotBB) {
        drawBox(frame, box, cv::Scalar(0, 0, 255), 1);
        cv::imshow("Frame", frame);
        temp.copyTo(frame);
        if (waitKey(20) == 27)
            return 1;
    }
    setMouseCallback("Frame", NULL, NULL);


    // Create some random colors
    vector<Scalar> colors = getRandomColors(100);

    Mat old_frame, old_gray;
    vector<Point2f> oldFeatures, newFeatures;
    // Take first frame and find corners in it
    capture >> old_frame;
    cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
    goodFeaturesToTrack(old_gray(box), oldFeatures, 50, 0.3, 7, Mat(), 7, false, 0.04);
    // Create a mask image for drawing purposes
    Mat mask = Mat::zeros(old_frame.size(), old_frame.type());
    while (true) {
        Mat frame_gray;
        if (frame.empty())
            break;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        // calculate optical flow
        vector<uchar> status;
        vector<float> err;
        TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
        calcOpticalFlowPyrLK(old_gray(box), frame_gray(box), oldFeatures, newFeatures, status, err, Size(15, 15), 2,
                             criteria);
        vector<Point2f> good_new = selectGoodFeaturesAndDrawTracks(oldFeatures, newFeatures, status, mask, frame,
                                                                   colors);

        updateBoxPosition(oldFeatures, newFeatures);
        rectangle(frame, box, cv::Scalar(0, 255, 0));

        Mat img;
        add(frame, mask, img);
        imshow("Frame", img);
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
        // Now update the previous frame and previous points
        old_gray = frame_gray.clone();
        oldFeatures = good_new;
        if (oldFeatures.size() < 5){
            goodFeaturesToTrack(frame_gray(box), oldFeatures, 50, 0.3, 7, Mat(), 7, false, 0.04);
        }
        cout << good_new.size() << endl;
        for (auto p: good_new) {
            cout << p << " ";
        }
        cout << endl;
        capture >> frame;
    }
}