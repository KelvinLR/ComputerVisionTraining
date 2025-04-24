#include <iostream>
#include <opencv2/opencv.hpp>
#define MAX_KERNEL_SIZE 30

using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    cv::Mat image, gray, small, big;

    image = cv::imread(argv[1], IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!\n";
    
    cv::cvtColor(image, gray, COLOR_BGR2GRAY); 
    std::cout << "Dimensões: " << image.cols << " x " << image.rows << std::endl;
    
    cv::namedWindow("Display Image", WINDOW_AUTOSIZE);
    cv::imshow("Display Image", gray);

    int k;

    double upscale = 2.0;
    double downscale = 0.5;
    cv::resize(gray, small, cv::Size(), downscale, downscale);
    cv::resize(gray, big, cv::Size(), upscale, upscale);

    do {
        k = waitKey(0);
        switch (k) {
            case '1':
                cv::imshow("Display Image", small);
                std::cout << "Dimensões: " << small.cols << " x " << small.rows << std::endl;
                cv::imwrite("small_beach.png", small);
                break;
            case '2':   
                cv::imshow("Display Image", big);
                std::cout << "Dimensões: " << big.cols << " x " << big.rows << std::endl;
                cv::imwrite("big_beach.png", big);
                break;
            case '3':   
                cv::imshow("Display Image", gray);
                std::cout << "Dimensões: " << gray.cols << " x " << gray.rows << std::endl;
                cv::imwrite("grey_beach.png", gray);
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
                break;
        }
    } while (k != 's');

    return 0;
}
