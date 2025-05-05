#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#define MAX_KERNEL_SIZE 30

using namespace std;

int main() {

    ifstream file("matrix.txt");
    string line;

    if (!file.is_open()) {
        std::cout << "Erro ao abrir o arquivo.\n";
        return -1;
    }

    while (std::getline(file, line)) {
        cout << line << std::endl;
    }

    file.close();

    cv::Mat image;
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);

    int k = waitKey(0);

    if(k == 's') {
        cv::imwrite("beachImage.png", image);
    }

    

   

    return 0;
}
