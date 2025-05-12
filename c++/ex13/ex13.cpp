#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#define MAX_KERNEL_SIZE 30

//using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    cv::Mat image;
    
    image = cv::imread(argv[1], cv::IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!\n";

    cv::Vec<unsigned char, 3> matrix[image.rows][image.cols];

    std::cout << matrix;
    cv::imshow("Imagem", image);
    cv::waitKey(0);
    cv::imwrite("beachImage.png", image); 

    return 0;
}
