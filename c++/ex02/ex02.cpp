#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    cv::Mat image, grey;

    image = cv::imread(argv[1], IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!\n";
    // cvtColor (semelhante ao memcpy no C)
    cv::cvtColor(image, grey, COLOR_BGR2GRAY); //image representa a Mat de origem, grey a de destino, e o parâmetro final é como a imagem será copiada
    std::cout << "Dimensões: " << image.cols << " x " << image.rows << std::endl;

    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", grey);

    int k = waitKey(0);

    if(k == 's') {
        cv::imwrite("greyaus02.png", grey);
    }

    return 0;
}
