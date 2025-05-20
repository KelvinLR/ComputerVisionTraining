#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#define FPS 60
int thresh_value = 127;
  
using namespace std;
using namespace cv;

void on_trackbar(int, void*) {}

int main() {
    VideoCapture cap(0);
    Mat frame, gray, threshold_bin;

    if (!cap.isOpened()) {
        std::cerr << "Erro: não foi possível acessar a câmera.\n";
        return -1;
    }
    
    namedWindow("Camera", WINDOW_AUTOSIZE);
    namedWindow("Cinza", WINDOW_AUTOSIZE);
    namedWindow("Threshold Bin", WINDOW_AUTOSIZE);
    double downscale = 0.2;
    cv::createTrackbar("Threshold", "Threshold Bin", &thresh_value, 255, on_trackbar);

    while(cap.read(frame)) {
        resize(frame, frame, cv::Size(), downscale, downscale);
        imshow("Camera", frame);

        int key = cv::waitKey(1000 / FPS);

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        cv::imshow("Cinza", gray);
        cv::threshold(gray, threshold_bin, thresh_value, 255, cv::THRESH_BINARY);
        cv::imshow("Threshold Bin", threshold_bin);
       
        if (key == 's') {
            cv::imwrite("tresholdFrame.png", threshold_bin);
            cv::imwrite("grayFrame.png", gray);    
        } else if (key == 'e') break;
        
    }

    return 0;
}
