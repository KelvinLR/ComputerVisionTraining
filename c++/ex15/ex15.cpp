#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#define FPS 60

using namespace std;
using namespace cv;

int main() {
    VideoCapture cap(0);
    Mat frame, gray, canny;

    if (!cap.isOpened()) {
        std::cerr << "Erro: não foi possível acessar a câmera.\n";
        return -1;
    }
    
    double downscale = 0.6;
    
    while(cap.read(frame)) {
        resize(frame, frame, cv::Size(), downscale, downscale);
        imshow("Camera", frame);

        int key = cv::waitKey(1000 / FPS);

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::imshow("Cinza", gray);
        cv::Canny(gray, canny ,10,350);
        cv::imshow("Canny", canny);
        
        if (key == 's') {
            cv::imwrite("CannyFrame.png", canny);
            cv::imwrite("grayFrame.png", gray);    
        } else if (key == 'e') break;
        
    }

    return 0;
}
