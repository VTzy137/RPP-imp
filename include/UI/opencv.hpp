#pragma once

#include "geometry/path.hpp"
#include "geometry/point.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>


class OpenCV
{
  public:
    static cv::Mat image;
    static void drawPoint(Point* point, cv::Scalar color = cv::Scalar(255, 0, 0));
    static void drawLine(Point* point1, Point* point2, cv::Scalar color = cv::Scalar(0, 255, 0));
    static void drawPath(Path* path, cv::Scalar color = cv::Scalar(0, 0, 255));
    static void showImage();
    static void showImage(int waitTime); // Show with custom wait time
    static void clearCanvas();           // Clear the canvas (undo all drawings)
    static void waitForKey();            // Wait until any key is pressed
    static void closeWindow();           // Close the display window
    static void example();
};