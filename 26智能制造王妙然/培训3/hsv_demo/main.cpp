#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 这里一定要确保你当前文件夹里有一张叫 test.jpg 或 test.png 的图片！
    Mat img = imread("test.png"); 
    if (img.empty()) {
        cout << "图片读取失败，请检查路径！" << endl;
        return -1;
    }

    Mat hsv;
    cvtColor(img, hsv, COLOR_BGR2HSV);

    vector<Mat> channels;
    split(hsv, channels);
    imshow("H Channel", channels[0]);
    imshow("S Channel", channels[1]);
    imshow("V Channel", channels[2]);

    Mat mask1, mask2, red_mask;
    inRange(hsv, Scalar(0, 70, 50), Scalar(10, 255, 255), mask1);
    inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), mask2);
    bitwise_or(mask1, mask2, red_mask);

    imshow("Red Mask", red_mask);
    imwrite("red_mask.png", red_mask);
    cout << "掩膜已保存为 red_mask.png" << endl;

    waitKey(0);
    return 0;
}
