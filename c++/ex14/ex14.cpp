#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#define FPS 60

using namespace std;
using namespace cv;

int main() {
    VideoCapture cap(0);
    Mat frame, gray;

    if (!cap.isOpened()) {
        std::cerr << "Erro: não foi possível acessar a câmera.\n";
        return -1;
    }
    
    double downscale = 0.2;
    
    while(cap.read(frame)) {
        resize(frame, frame, cv::Size(), downscale, downscale);
        imshow("Camera", frame);

        int key = cv::waitKey(1000 / FPS);

        if (key == 'g') {
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            cv::imshow("Cinza", gray);
            cv::imwrite("grayFrame.png", gray);
            std::cout << "Imagem em tons de cinza salva como grayFrame.png\n";
        } else if (key == 'q') {
            break;
        }
    }

    return 0;
}
