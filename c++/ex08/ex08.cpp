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

    do {
        k = waitKey(0);
        switch (k) {
            case '1':
                cv::imshow("Display Image", small);
                cv::imwrite("small_beach.png", small);
                break;
            case '2':   
                cv::imshow("Display Image", big);
                cv::imwrite("big_beach.png", big);
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
                break;
        }
    } while (k != 's');

    return 0;
}
