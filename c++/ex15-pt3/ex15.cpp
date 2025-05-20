#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#define FPS 60

using namespace std;
using namespace cv;

int main() {
    VideoCapture cap(0);
    Mat frame, gray;
    int Gx, Gy, magnitude;

    if (!cap.isOpened()) {
        std::cerr << "Erro: não foi possível acessar a câmera.\n";
        return -1;
    }
    
    double downscale = 0.8;
    
    while(cap.read(frame)) {
        resize(frame, frame, cv::Size(), downscale, downscale);
        imshow("Camera", frame);

        int key = cv::waitKey(1000 / FPS);

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::imshow("Cinza", gray);
        Mat_<uchar> sobel_filter(gray.rows, gray.cols, 1);

        for (int y = 1; y < gray.rows - 1; y++) {
            for (int x = 1; x < gray.cols - 1; x++) {
                Gx = (1)*gray.at<uchar>(y-1,x-1) + (2)*gray.at<uchar>(y-1,x) + (1)*gray.at<uchar>(y-1,x+1) + (-1)*gray.at<uchar>(y+1,x-1) + (-2)*gray.at<uchar>(y+1,x) + (-1)*gray.at<uchar>(y+1,x+1);
                Gy = (1)*gray.at<uchar>(y-1,x-1) + (-1)*gray.at<uchar>(y-1,x+1) + (2)*gray.at<uchar>(y,x-1) + (-2)*gray.at<uchar>(y,x+1) + (1)*gray.at<uchar>(y+1,x-1) + (-1)*gray.at<uchar>(y+1,x+1); 
    
                magnitude = (int)sqrt(pow(Gx, 2) + pow(Gy, 2));
                sobel_filter.at<uchar>(y,x) = magnitude;
            }
        }

        cv::imshow("Sobel", sobel_filter);
        
        if (key == 's') {
            cv::imwrite("sobelFrame.png", sobel_filter);
            cv::imwrite("grayFrame.png", gray);    
        } else if (key == 'e') break;
        
    }

    return 0;
}
