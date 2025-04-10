#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    // Criando variáveis para imagem e seus respectivos canais
    cv::Mat image, rChannel, gChannel, bChannel;
    std::vector<Mat> channels;

    image = cv::imread(argv[1], IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    cv::split(image, channels);

    std::cout << "Imagem carregada com sucesso!\n";
    // Exibindo as dimensões da imagem
    std::cout << "Dimensões: " << image.cols << " x " << image.rows << std::endl; 
    std::cout << "Canais da imagem: " << image.channels() << std::endl; 


    // Detectando entrada do teclado
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);

    int k = waitKey(0);

    switch(k) {
        case 'r':
            imshow("Display Image", channels[2]); // R
            break;
        case 'g':
            imshow("Display Image", channels[1]); // G
            break;
        case 'b':
            imshow("Display Image", channels[0]); // B
            break;
        default:
            imwrite("greyaus02.png", image);
            std::cout << "Imagem salva como greyaus02.png\n";
            break;
    }

    waitKey(0); 
    return 0;

}
