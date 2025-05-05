#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#define MAX_KERNEL_SIZE 30

using namespace std;

int main() {
    fstream file("matrix.txt");
    string line;
    int cols = 0, rows = 0;

    if (!file.is_open()) {
        cout << "Erro ao abrir o arquivo.\n";
        return -1;
    }

    while (std::getline(file, line)) {
        if (rows == 0) {
            std::istringstream ss(line);
            int value, count = 0;
            while (ss >> value) count++;
            cols = count / 3;
        }
        rows++;
    }

    cout << rows << "x" << cols << std::endl;

    cv::Mat image(rows, cols, CV_8UC3);

    file.clear();
    file.seekg(0, ios::beg);
    int row = 0;

    while (std::getline(file, line) && row < rows) {
        std::istringstream ss(line);
        int r, g, b;
        int col = 0;

        while (col < cols && ss >> r >> g >> b) {
            image.at<cv::Vec3b>(row, col) = cv::Vec3b(b, g, r);
            col++;
        }

        row++;
    }

    file.close();

    cv::imshow("Imagem", image);
    cv::waitKey(0);
    cv::imwrite("beachImage.png", image); 

    return 0;
}
