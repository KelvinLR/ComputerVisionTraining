#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    cv::Mat image, hsv;

    image = cv::imread(argv[1], IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!\n";
    
    cv::cvtColor(image, hsv, COLOR_BGR2HSV); //image representa a Mat de origem, grey a de destino, e o parâmetro final é como a imagem será copiada
    std::cout << "Dimensões: " << image.cols << " x " << image.rows << std::endl;

    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", hsv);

    int k = waitKey(0);

    if(k == 's') {
        cv::imwrite("hsvausimage.png", hsv);
    }

    return 0;
}
