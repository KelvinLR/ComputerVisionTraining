#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#define MAX_KERNEL_SIZE 30

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    Mat image, small;
    Mat_<uchar> gray_image;

    int Gx, Gy, magnitude;
    
    image = imread(argv[1], IMREAD_COLOR);
    cvtColor(image, gray_image, COLOR_BGR2GRAY);

    if (!image.data) {
        cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    cout << "Imagem carregada com sucesso!\n";

    double downscale = 0.7;
    cv::resize(gray_image, gray_image, cv::Size(), downscale, downscale);

    Mat_<uchar> sobel_filter(gray_image.rows, gray_image.cols, 1); 

    for (int y = 1; y < gray_image.rows - 1; y++) {
        for (int x = 1; x < gray_image.cols - 1; x++) {
            Gx = (1)*gray_image.at<uchar>(y-1,x-1) + (2)*gray_image.at<uchar>(y-1,x) + (1)*gray_image.at<uchar>(y-1,x+1) + (-1)*gray_image.at<uchar>(y+1,x-1) + (-2)*gray_image.at<uchar>(y+1,x) + (-1)*gray_image.at<uchar>(y+1,x+1);
            Gy = (1)*gray_image.at<uchar>(y-1,x-1) + (-1)*gray_image.at<uchar>(y-1,x+1) + (2)*gray_image.at<uchar>(y,x-1) + (-2)*gray_image.at<uchar>(y,x+1) + (1)*gray_image.at<uchar>(y+1,x-1) + (-1)*gray_image.at<uchar>(y+1,x+1); 

            magnitude = (int)sqrt(pow(Gx, 2) + pow(Gy, 2));
            sobel_filter.at<uchar>(y,x) = magnitude;
        }
    }

    cv::namedWindow("Display Image", WINDOW_AUTOSIZE);

    int k;

    do {
        k = waitKey(0);
        switch (k) {
            case '1': 
                cv::imshow("Display Image", image);
                std::cout << "Dimensões: " << image.cols << " x " << image.rows << std::endl;
                cv::imwrite("original.png", image);
                break;
            case '2':   
                cv::imshow("Display Image", gray_image);
                std::cout << "Dimensões: " << gray_image.cols << " x " << gray_image.rows << std::endl;
                cv::imwrite("grayAussieMap.png", gray_image);
                break;
            case '3':   
                cv::imshow("Display Image", sobel_filter);
                std::cout << "Dimensões: " << sobel_filter.cols << " x " << sobel_filter.rows << std::endl;
                cv::imwrite("aussieMapSobel.png", sobel_filter);
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
                break;
        }
    } while (k != 's');

    return 0;
}
