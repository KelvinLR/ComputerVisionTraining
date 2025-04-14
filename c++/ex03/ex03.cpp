#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat getColoredChannel(const Mat& image, int channelIndex) {
    std::vector<Mat> zeros(3, Mat::zeros(image.size(), CV_8UC1));
    Mat extracted;

    extractChannel(image, extracted, channelIndex);
    zeros[channelIndex] = extracted;
    Mat result;
    merge(zeros, result);

    return result;
}

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

   
    int k;

    do {
        std::cout << "\n[r] vermelho | [g] verde | [b] azul | [s] sair\n";
        k = waitKey(0);

        Mat canalColorido;
        std::string nome;

        switch(k) {
            case 'r':
                canalColorido = getColoredChannel(image, 2); // R
                imshow("Display Image", canalColorido);
                imwrite("ausRchannel.png", canalColorido);
                std::cout << "Imagem salva como ausRchannel.png\n";
                break;
            case 'g':
                canalColorido = getColoredChannel(image, 1); // G
                imshow("Display Image", canalColorido);
                imwrite("ausGchannel.png", canalColorido);
                std::cout << "Imagem salva como ausGchannel.png\n";
                break;
            case 'b':
                canalColorido = getColoredChannel(image, 0); // B
                imshow("Display Image", canalColorido);
                imwrite("ausBchannel.png", canalColorido);
                std::cout << "Imagem salva como ausBchannel.png\n";
                break;
            default:
                imwrite("greyaus02.png", image);
                std::cout << "Imagem original salva como greyaus02.png\n";
                break;
        }

    } while (k != 's');

    // waitKey(0); 
    return 0;

}
