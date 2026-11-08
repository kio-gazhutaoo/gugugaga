#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

int main() {
    // 确保你的视频就在这个文件夹里，并且叫这个名字
    VideoCapture cap("test.mp4");
    if (!cap.isOpened()) {
        cout << "无法打开视频，请检查路径！" << endl;
        return -1;
    }

    Mat frame, hsv, mask;
    
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // 转 HSV 并提取红色
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        Mat mask1, mask2;
        inRange(hsv, Scalar(0, 70, 50), Scalar(10, 255, 255), mask1);
        inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), mask2);
        bitwise_or(mask1, mask2, mask);

        // 形态学操作去噪
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        morphologyEx(mask, mask, MORPH_OPEN, kernel);
        dilate(mask, mask, kernel);

        // 找轮廓
        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        vector<RotatedRect> light_bars;
        
        // 筛选灯条
        for (size_t i = 0; i < contours.size(); i++) {
            double area = contourArea(contours[i]);
            if (area > 50 && area < 5000) { 
                RotatedRect rect = minAreaRect(contours[i]);
                float w = rect.size.width;
                float h = rect.size.height;
                float ratio = max(w, h) / min(w, h);
                if (ratio > 2.0) {
                    light_bars.push_back(rect);
                }
            }
        }

        // 如果找到两个以上灯条，画框
        if (light_bars.size() >= 2) {
            sort(light_bars.begin(), light_bars.end(), [](RotatedRect a, RotatedRect b) {
                return a.center.x < b.center.x;
            });

            RotatedRect left_bar = light_bars[0];
            RotatedRect right_bar = light_bars[1];

            Point2f left_pts[4], right_pts[4];
            left_bar.points(left_pts);
            right_bar.points(right_pts);
            // 画黄色小框
            for (int j = 0; j < 4; j++) {
                line(frame, left_pts[j], left_pts[(j + 1) % 4], Scalar(0, 255, 255), 2);
                line(frame, right_pts[j], right_pts[(j + 1) % 4], Scalar(0, 255, 255), 2);
            }

            // 计算装甲板四个角
            vector<Point2f> armor_pts(4);
            armor_pts[0] = Point2f(min(left_pts[0].x, left_pts[1].x), min(left_pts[0].y, left_pts[1].y)); 
            armor_pts[1] = Point2f(max(right_pts[2].x, right_pts[3].x), min(right_pts[2].y, right_pts[3].y)); 
            armor_pts[2] = Point2f(max(right_pts[2].x, right_pts[3].x), max(right_pts[2].y, right_pts[3].y)); 
            armor_pts[3] = Point2f(min(left_pts[0].x, left_pts[1].x), max(left_pts[0].y, left_pts[1].y)); 

            // 画绿色角点
            for (int j = 0; j < 4; j++) {
                circle(frame, armor_pts[j], 5, Scalar(0, 255, 0), -1);
            }

            // 画蓝色连线大框
            for (int j = 0; j < 4; j++) {
                line(frame, armor_pts[j], armor_pts[(j + 1) % 4], Scalar(255, 0, 0), 2);
            }
        }

        // 显示画面
        imshow("Detection", frame);
        imshow("Mask", mask);

        // 按 ESC 退出
        if (waitKey(30) == 27) break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
