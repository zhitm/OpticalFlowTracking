#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstring>
#include <opencv2/core/types_c.h>

using namespace std;
using namespace cv;

bool gotBB = false;
bool drawing_box = false;
cv::Rect2i box;


int main(int argc, char **argv) {
    // show help
    if (argc < 2) {
        cout <<
             " Usage: tracker <video_name>\n"
             " examples:\n"
             " example_tracking_kcf Bolt/img/%04d.jpg\n"
             " example_tracking_kcf faceocc2.webm\n"
             << endl;
        return 0;
    }
    VideoCapture capture(argv[1]);
    if (!capture.isOpened()) {
        //error in opening the video input
        cerr << "Unable to open file!" << endl;
        return 0;
    }


    cv::Mat frame;


    Ptr<Tracker> tracker = TrackerKCF::create();
    capture >> frame;
    box = selectROI("Frame", frame);
    //quit if ROI was not selected
    if (box.width == 0 || box.height == 0)
        return 0;
    // initialize the tracker
    tracker->init(frame, box);
    // perform the tracking process
    printf("Start the tracking process, press ESC to quit.\n");
    for (;;) {
        // get frame from the video
        capture >> frame;
        // stop the program if no more images
        if (frame.rows == 0 || frame.cols == 0)
            break;
        // update the tracking result
        tracker->update(frame, box);
        // draw the tracked object
        rectangle(frame, box, Scalar(255, 0, 0), 2, 1);
        // show image with the tracked object
        imshow("tracker", frame);
        //quit on ESC button
        if (waitKey(1) == 27)break;
    }
    return 0;
}