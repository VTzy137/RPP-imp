#include "UI/opencv.hpp"
#include "geometry/map.hpp"
#include <thread>

cv::Mat OpenCV::image = cv::Mat(1000, 1000, CV_8UC3, cv::Scalar(255, 255, 255));
cv::Mat OpenCV::imageMap = cv::Mat(1000, 1000, CV_8UC3, cv::Scalar(255, 255, 255));

void OpenCV::drawPoint(Point* point, cv::Scalar color)
{
    if (point != nullptr)
    {
        cv::circle(image, cv::Point(point->x * ratio, point->y * ratio), 2, color, -1);
    }
}

void OpenCV::drawLine(Point* point1, Point* point2, int thickness, cv::Scalar color)
{
    cv::line(image, cv::Point(point1->x * ratio, point1->y * ratio), cv::Point(point2->x * ratio, point2->y * ratio),
             color, thickness);
}

void OpenCV::drawPath(Path* path, cv::Scalar color)
{
    Point* current = path->begin;
    while (current != nullptr && current->nextPoint != nullptr)
    {
        drawPoint(current, color);
        drawLine(current, current->nextPoint, 1, color);
        current = current->nextPoint;
    }
}

void OpenCV::showPopulation(int time)
{
    for (int individualIndex = 0; individualIndex < Path::population.size(); ++individualIndex)
    {
        OpenCV::drawPath(Path::population[individualIndex]);
        // OpenCV::drawPath(Path::population[individualIndex], cv::Scalar(200, 200, 0));
    }
    OpenCV::showImage(time);
}

void OpenCV::showImage(int waitTime)
{
    if (waitTime == 0)
    {
        cv::imshow("Image", image);
        OpenCV::waitForKey();
    }
    else
    {
        cv::imshow("Image", image);
        cv::waitKey(waitTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    }
    OpenCV::clearCanvasWithMap();
}

void OpenCV::clearCanvas()
{
    image = cv::Mat(1000, 1000, CV_8UC3, cv::Scalar(255, 255, 255));
}

void OpenCV::waitForKey()
{
    cv::waitKey(0);
}

void OpenCV::closeWindow()
{
    cv::destroyAllWindows();
}

void OpenCV::initColorLUT()
{
    colorLUT.resize(256);
    cv::Mat gray(1, 1, CV_8UC1), color;
    colorLUT[0] = cv::Scalar(256, 256, 256);
    for (int i = 1; i < 256; ++i)
    {
        gray.at<uchar>(0, 0) = i;
        cv::applyColorMap(gray, color, cv::COLORMAP_JET);
        cv::Vec3b bgr = color.at<cv::Vec3b>(0, 0);
        colorLUT[i] = cv::Scalar(bgr[0], bgr[1], bgr[2]);
    }
}

void OpenCV::calcResize()
{
    ratio = std::min(1000.0f / Map::mapHeight, 1000.0f / Map::mapWidth);
    OpenCV::initColorLUT();
}

void OpenCV::saveMapGradient()
{
    imageMap = cv::Mat(1000, 1000, CV_8UC3, cv::Scalar(0, 0, 0));

    for (int i = 0; i < Map::mapHeight && i < 1000; i++)
    {
        for (int j = 0; j < Map::mapWidth && j < 1000; j++)
        {
            int gradientValue = Map::mapGradient[i][j];
            if (gradientValue > 0)
            {
                cv::Scalar color = getGradientColor(gradientValue);
                int x = static_cast<int>(j * ratio);
                int y = static_cast<int>(i * ratio);

                // cv::rectangle(imageMap, cv::Point(x, y),
                //               cv::Point(x + static_cast<int>(ratio) + 1, y + static_cast<int>(ratio) + 1), color,
                //               -1);
                cv::rectangle(imageMap, cv::Point(x, y),
                              cv::Point(x + static_cast<int>(ratio) + 1, y + static_cast<int>(ratio) + 1),
                              cv::Scalar(255, 255, 255), -1);
            }
        }
    }

    cv::circle(imageMap, cv::Point(Map::startPoint.x * ratio, Map::startPoint.y * ratio), 3, cv::Scalar(0, 0, 255), -1);
    cv::circle(imageMap, cv::Point(Map::finishPoint.x * ratio, Map::finishPoint.y * ratio), 3, cv::Scalar(0, 0, 255),
               -1);
    cv::circle(imageMap, cv::Point(Map::startPoint.x * ratio, Map::startPoint.y * ratio), 2, cv::Scalar(0, 0, 255), -1);
    cv::circle(imageMap, cv::Point(Map::finishPoint.x * ratio, Map::finishPoint.y * ratio), 2, cv::Scalar(0, 0, 255),
               -1);
    cv::circle(imageMap, cv::Point(Map::startPoint.x * ratio, Map::startPoint.y * ratio), 1, cv::Scalar(0, 0, 255), -1);
    cv::circle(imageMap, cv::Point(Map::finishPoint.x * ratio, Map::finishPoint.y * ratio), 1, cv::Scalar(0, 0, 255),
               -1);
    for (auto& obstacle : Map::obstacles)
    {
        Point* current = obstacle;
        while (current != nullptr && current->nextPoint != nullptr)
        {
            cv::line(imageMap, cv::Point(current->x * ratio, current->y * ratio),
                     cv::Point(current->nextPoint->x * ratio, current->nextPoint->y * ratio), cv::Scalar(0, 0, 0), 3);
            current = current->nextPoint;
        }
        cv::line(imageMap, cv::Point(current->x * ratio, current->y * ratio),
                 cv::Point(obstacle->x * ratio, obstacle->y * ratio), cv::Scalar(0, 0, 0), 3);
    }
    OpenCV::clearCanvasWithMap();
}

void OpenCV::clearCanvasWithMap()
{
    imageMap.copyTo(image);
}

cv::Scalar OpenCV::getGradientColor(float value)
{
    float minVal = 800000, maxVal = 1300000;
    float normalized = 255.0f * (value - minVal) / (maxVal - minVal);
    int index = static_cast<int>(std::clamp(normalized, 0.0f, 255.0f));
    return OpenCV::colorLUT[index];
}
