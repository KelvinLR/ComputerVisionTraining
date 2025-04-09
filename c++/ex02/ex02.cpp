#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    cv::Mat image, imB, imC, grey;

    image = cv::imread(argv[1], IMREAD_COLOR);
    grey_image = cv::cvtColor(img, grey, COLOR_BGR2GRAY);

    if (!image.data) {
        std::cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    //imB = image.clone(); 
    //imC = image;          

    std::cout << "Imagem carregada com sucesso!\n";
    std::cout << "Dimensões: " << image.cols << " x " << image.rows << std::endl;

    imwrite("saida.jpg", imB);  

    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", grey_image);

    int k = waitKey(0);

    if(k == 's') {
        grey_image = cv::cvtColor(img, grey, COLOR_BGR2GRAY);
        cv::imwrite("greyaus02.png", grey_image);
    }

    return 0;
}
