#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat getColoredChannel(const Mat& image, int channelIndex) {
    // criando array de canais
    // e extraindo o canal desejado
    // e preenchendo os outros canais com zeros
    std::vector<Mat> zeros(3, Mat::zeros(image.size(), CV_8UC1));
    Mat extracted;

    // extraindo canal e copiando para o vetor de canais
    // e preenchendo os outros canais com zeros
    // o canal desejado é o canalIndex
    // e os outros canais são preenchidos com zeros
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

    cv::Mat image, hsv;

    image = cv::imread(argv[1], IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!\n";
    
    cv::cvtColor(image, hsv, COLOR_BGR2HSV); //image representa a Mat de origem, hsv a de destino, e o parâmetro final é como a imagem será copiada
    std::cout << "Dimensões: " << image.cols << " x " << image.rows << std::endl;

    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", hsv); 
    // numa imagem HSV os canais não representam cores 
    // mas atributos como matiz [h], saturação [s] e valor [v]

    int k;

    do {
        std::cout << "\n[h] hue | [s] saturation | [v] value | [u] sair\n";
        k = waitKey(0);

        Mat canalColorido;
        std::string nome;

        switch(k) {
            case 'h':
                canalColorido = getColoredChannel(hsv, 2); // H
                imshow("Display Image", canalColorido);
                imwrite("ausHchannel.png", canalColorido);
                std::cout << "Imagem salva como ausRchannel.png\n";
                break;
            case 's':
                canalColorido = getColoredChannel(hsv, 1); // S
                imshow("Display Image", canalColorido);
                imwrite("ausSchannel.png", canalColorido);
                std::cout << "Imagem salva como ausGchannel.png\n";
                break;
            case 'v':
                canalColorido = getColoredChannel(hsv, 0); // V
                imshow("Display Image", canalColorido);
                imwrite("ausVchannel.png", canalColorido);
                std::cout << "Imagem salva como ausBchannel.png\n";
                break;
            default:
                imwrite("greyaus02.png", hsv);
                std::cout << "Imagem original salva como greyaus02.png\n";
                break;
        }

    } while (k != 'u');

    // waitKey(0);
    return 0;
}
