#pragma once

#include "geometry/path.hpp"
#include "geometry/point.hpp"
#include <algorithm>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>


class OpenCV
{
  private:
    inline static std::vector<cv::Scalar> colorLUT;
    static void initColorLUT();

  public:
    static cv::Mat image;
    static cv::Mat imageMap;
    inline static float ratio = 1.0f;
    static void calcResize();
    static void drawPoint(Point* point, cv::Scalar color = cv::Scalar(255, 0, 0));
    static void drawLine(Point* point1, Point* point2, int thickness = 1, cv::Scalar color = cv::Scalar(0, 0, 0));
    static void drawPath(Path* path, cv::Scalar color = cv::Scalar(200, 200, 200));
    static void showImage();
    static void showImage(int waitTime);
    static void clearCanvas();
    static void saveMapGradient();
    static void clearCanvasWithMap();
    static void waitForKey();
    static void closeWindow();
    static cv::Scalar getGradientColor(float value);
};