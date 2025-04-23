#include <iostream>
#include <opencv2/opencv.hpp>
#define MAX_KERNEL_SIZE 30

using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    cv::Mat image, gray, canny;

    std::vector<int> arr;

    

    image = cv::imread(argv[1], IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!\n";
    
    cv::cvtColor(image, gray, COLOR_BGR2GRAY); 
    std::cout << "Dimensões: " << image.cols << " x " << image.rows << std::endl;

    cv::Canny(gray, canny ,10,350);
    
    cv::namedWindow("Display Image", WINDOW_AUTOSIZE);
    cv::imshow("Display Image", canny);

    int k;

    k = waitKey(0);

    if (k == 's') {
      cv::imwrite("canny_aus.png", canny);
    }

    return 0;
}
