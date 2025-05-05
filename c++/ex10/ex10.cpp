#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#define MAX_KERNEL_SIZE 30

using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    cv::Mat image, gray;
    std::ofstream myFile;
    myFile.open("matrix.txt");

    image = cv::imread(argv[1], IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Não foi possível abrir ou encontrar a imagem\n";
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!\n";

    cv::Vec<unsigned char, 3> matrix[image.rows][image.cols];
    
    std::vector<cv::Mat> images;

    for(int limiar = 0; limiar < 128; limiar++) {
        cv::Mat imagemLimiarizada(image.rows, image.cols, CV_8UC1);
        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {
                matrix[i][j] = image.at<cv::Vec3b>(i, j);
                cv::Vec3b pixel = matrix[i][j];
                int R = pixel[2];
                int G = pixel[1];
                int B = pixel[0];
        
                int media = (R + G + B) / 3;
        
                if (media > limiar) {
                    imagemLimiarizada.at<uchar>(i, j) = 255;
                } else {
                    imagemLimiarizada.at<uchar>(i, j) = 0;
                }
            }
        }
        images.push_back(imagemLimiarizada);
    }
    
    cv::cvtColor(image, gray, COLOR_BGR2GRAY); 
    std::cout << "Dimensões: " << image.cols << " x " << image.rows << std::endl;

    for(int i = 0; i < image.rows; i++) {
        for(int j = 0; j < image.cols; j++) {
            myFile << (int)matrix[i][j][0] << (int)matrix[i][j][1] << (int)matrix[i][j][2];
            std::cout << matrix[i][j] << " ";
        }
    }
   
    myFile.close();
    
    cv::namedWindow("Limiarizacao", cv::WINDOW_AUTOSIZE);
    while (true) {
        for (int i = 0; i < images.size(); i++) {
            cv::imshow("Limiarizacao", images[i]);
            if (cv::waitKey(50) == 27) 
                return 0;
        }
    }
    cv::destroyAllWindows();

    int k;
    k = waitKey(0);

    return 0;
}
