#include "UI/opencv.hpp"

cv::Mat OpenCV::image = cv::Mat(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));

void OpenCV::drawPoint(Point* point, cv::Scalar color)
{
    if (point != nullptr)
    {
        cv::circle(image, cv::Point(point->x, point->y), 2, color, -1);
    }
}

void OpenCV::drawLine(Point* point1, Point* point2, cv::Scalar color)
{
    cv::line(image, cv::Point(point1->y, point1->x), cv::Point(point2->y, point2->x), color, 2);
}

void OpenCV::drawPath(Path* path, cv::Scalar color)
{
    Point* current = path->begin;
    while (current != nullptr)
    {
        drawLine(current, current->nextPoint, color);
        current = current->nextPoint;
    }
}

void OpenCV::showImage()
{
    cv::imshow("Image", image);
}

void OpenCV::showImage(int waitTime)
{
    cv::imshow("Image", image);
    cv::waitKey(waitTime);
}

void OpenCV::clearCanvas()
{
    image = cv::Mat(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));
}

void OpenCV::waitForKey()
{
    cv::waitKey(0); // Wait indefinitely until any key is pressed
}

void OpenCV::closeWindow()
{
    cv::destroyAllWindows();
}

void OpenCV::example()
{
    // Demo 1: Draw some points
    std::cout << "1. Drawing points..." << std::endl;
    drawPoint(new Point(100, 100)); // Red point (default)
    drawPoint(new Point(150, 150));
    drawPoint(new Point(200, 100));
    drawPoint(new Point(250, 150));
    showImage(1500); // Show for 1.5 seconds

    // Demo 2: Add some lines
    std::cout << "2. Adding lines..." << std::endl;
    drawLine(new Point(100, 100), new Point(250, 150)); // Green line (default)
    drawLine(new Point(150, 150), new Point(200, 100));
    showImage(1500);

    // Demo 3: Clear and draw a simple pattern
    std::cout << "3. Clearing canvas and drawing a pattern..." << std::endl;
    clearCanvas();

    // Draw a simple cross pattern
    drawLine(new Point(250, 150), new Point(250, 350)); // Vertical line
    drawLine(new Point(150, 250), new Point(350, 250)); // Horizontal line
    showImage(1000);

    // Demo 4: Add corner points
    std::cout << "4. Adding corner points..." << std::endl;
    drawPoint(new Point(50, 50));   // Top-left
    drawPoint(new Point(450, 50));  // Top-right
    drawPoint(new Point(50, 450));  // Bottom-left
    drawPoint(new Point(450, 450)); // Bottom-right
    showImage(1000);

    // Demo 5: Connect the corners
    std::cout << "5. Connecting corners..." << std::endl;
    drawLine(new Point(50, 50), new Point(450, 50));   // Top edge
    drawLine(new Point(450, 50), new Point(450, 450)); // Right edge
    drawLine(new Point(450, 450), new Point(50, 450)); // Bottom edge
    drawLine(new Point(50, 450), new Point(50, 50));   // Left edge
    showImage(2000);

    // Demo 6: Wait for user input
    std::cout << "6. Press any key to continue..." << std::endl;
    waitForKey();

    // Demo 7: Random lines demonstration
    std::cout << "7. Drawing random lines..." << std::endl;
    clearCanvas();
    for (int i = 0; i < 5; i++)
    {
        drawLine(new Point(rand() % 500, rand() % 500), new Point(rand() % 500, rand() % 500));
        showImage(500); // Brief pause between each line
    }
}