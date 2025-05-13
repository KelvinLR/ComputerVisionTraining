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

    Mat image;
    Mat_<uchar> gray_image;

    int Gx, Gy;
    
    image = imread(argv[1], IMREAD_COLOR);
    cvtColor(image, gray_image, COLOR_BGR2GRAY);

    if (!image.data) {
        cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    cout << "Imagem carregada com sucesso!\n";

    Mat_<uchar> sobel_filter(gray_image.rows, gray_image.cols, 1);

    for (int y = 1; y < gray_image.rows - 1; y++) {
        for (int x = 1; x < gray_image.cols - 1; x++) {
            Gx = (1)*gray_image.at<uchar>(y-1,x-1) + (2)*gray_image.at<uchar>(y-1,x) + (1)*gray_image.at<uchar>(y-1,x+1) + (-1)*gray_image.at<uchar>(y+1,x-1) + (-2)*gray_image.at<uchar>(y+1,x) + (-1)*gray_image.at<uchar>(y+1,x+1);
            Gy = (1)*gray_image.at<uchar>(y-1,x-1) + (-1)*gray_image.at<uchar>(y-1,x+1) + (2)*gray_image.at<uchar>(y,x-1) + (-2)*gray_image.at<uchar>(y,x+1) + (1)*gray_image.at<uchar>(y+1,x-1) + (-1)*gray_image.at<uchar>(y+1,x+1); 

            sobel_filter.at<uchar>(y,x) = (int)sqrt(pow(Gx, 2) + pow(Gy, 2));
        }
    }
    
    imshow("Imagem", sobel_filter);
    waitKey(0);
    imwrite("aussieSobel.png", image); 

    return 0;
}
