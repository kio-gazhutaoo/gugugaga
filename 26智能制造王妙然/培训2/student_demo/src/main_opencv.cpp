#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 读取一张图片（注意：确保你虚拟机里有一张叫 test.jpg 的图片，或者改成绝对路径）
    cv::Mat img = cv::imread("test.jpg"); 
    if (img.empty()) {
        std::cout << "无法读取图片，请检查路径！" << std::endl;
        return -1;
    }
    // 显示图片
    cv::imshow("OpenCV Test", img);
    cv::waitKey(0);
    return 0;
}
