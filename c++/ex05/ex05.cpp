#include <iostream>
#include <opencv2/opencv.hpp>
#define MAX_KERNEL_SIZE 30

using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    cv::Mat image, gray, medianBlurred, bilateralFiltered, gaussianBlurred;

    image = cv::imread(argv[1], IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!\n";
    
    cv::cvtColor(image, gray, COLOR_BGR2GRAY); 
    std::cout << "Dimensões: " << image.cols << " x " << image.rows << std::endl;
    
    cv::medianBlur(gray, medianBlurred, 5); 
    cv::GaussianBlur(gray, gaussianBlurred, Size(5, 5), 0);
    cv::bilateralFilter(gray, bilateralFiltered, 9, 75, 75);
          
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", gray);
    
    int k;

    do {
        std::cout << "\n[g] gaussian / [m] median / [b] bilateral / [s] sair \n";
        k = waitKey(0);

        Mat canalColorido;
        std::string nome;

        switch(k) {
            case 'g':
                imshow("Display Image", gaussianBlurred);
                imwrite("ausGaussianBlurred.png", gaussianBlurred);
                std::cout << "Imagem salva como ausGaussianBlurred.png\n";
                break;
            case 'm':
                imshow("Display Image", medianBlurred);
                imwrite("ausMedianBlurred.png", medianBlurred);
                std::cout << "Imagem salva como ausMedianBlurred.png\n";
                break;
            case 'b':
                imshow("Display Image", bilateralFiltered);
                imwrite("ausBilateralFiltered.png", bilateralFiltered);
                std::cout << "Imagem salva como ausBilateralFiltered.png\n";
                break; 
            default:
                imwrite("greyaus02.png", image);
                std::cout << "Imagem original salva como greyaus02.png\n";
                break;
        }

    } while (k != 's');

    return 0;
}
