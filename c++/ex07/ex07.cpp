#include <iostream>
#include <opencv2/opencv.hpp>
#define MAX_KERNEL_SIZE 30

using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    cv::Mat image, gray, thrs1, thrs2, thrs3, thrs4, thrs5, thrs6, thrs7;

    image = cv::imread(argv[1], IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!\n";
    
    cv::cvtColor(image, gray, COLOR_BGR2GRAY); 
    std::cout << "Dimensões: " << image.cols << " x " << image.rows << std::endl;

    cv::threshold(gray, thrs1, 127, 255, THRESH_BINARY);
    cv::threshold(gray, thrs2, 127, 255, THRESH_BINARY_INV);
    cv::threshold(gray, thrs3, 127, 255, THRESH_TRUNC);
    cv::threshold(gray, thrs4, 127, 255, THRESH_TOZERO);
    cv::threshold(gray, thrs5, 127, 255, THRESH_TOZERO_INV);
    cv::adaptiveThreshold(gray, thrs6, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2);
    cv::adaptiveThreshold(gray, thrs7, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);
    
    
    cv::namedWindow("Display Image", WINDOW_AUTOSIZE);
    cv::imshow("Display Image", gray);

    int k;

    do {
        k = waitKey(0);
        switch (k) {
            case '1':
                cv::imshow("Display Image", thrs1);
                cv::imwrite("thrs1_beach.png", thrs1);
                break;
            case '2':   
                cv::imshow("Display Image", thrs2);
                cv::imwrite("thrs2_beach.png", thrs2);
                break;
            case '3':
                cv::imshow("Display Image", thrs3);
                cv::imwrite("thrs3_beach.png", thrs3);
                break;
            case '4':   
                cv::imshow("Display Image", thrs4);
                cv::imwrite("thrs4_beach.png", thrs4);
                break;
            case '5':
                cv::imshow("Display Image", thrs5);
                cv::imwrite("thrs5_beach.png", thrs5);
                break;
            case '6':
                cv::imshow("Display Image", thrs6);
                cv::imwrite("thrs6_beach.png", thrs6);
                break;
            case '7':
                cv::imshow("Display Image", thrs7);
                cv::imwrite("thrs7_beach.png", thrs7);
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
                break;
        }
    } while (k != 's');

    return 0;
}
