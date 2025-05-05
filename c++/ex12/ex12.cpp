#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#define MAX_KERNEL_SIZE 30

using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    cv::Mat image, gray, thr;

    image = cv::imread(argv[1], IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!\n";
    
    cv::cvtColor(image, gray, COLOR_BGR2GRAY); 
    cv::threshold(gray, thr, 100,255,THRESH_BINARY);

    std::cout << "Dimensões: " << image.cols << " x " << image.rows << std::endl;

    Moments m = moments(thr,true);
    Point p(m.m10/m.m00, m.m01/m.m00);

    circle(image, p, 5, Scalar(128,0,0), -1);
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);

    int k = waitKey(0);

    if(k == 's') {
        cv::imwrite("greyaus02.png", thr);
    }

    return 0;
}
