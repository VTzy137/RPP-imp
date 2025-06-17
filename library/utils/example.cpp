
#include <UI/opencv.hpp>
#include <utils/example.hpp>


void UseExample::example()
{
    // Demo 1: Draw some points
    std::cout << "1. Drawing points..." << std::endl;
    OpenCV::drawPoint(new Point(100, 100));
    OpenCV::drawPoint(new Point(150, 150));
    OpenCV::drawPoint(new Point(200, 100));
    OpenCV::drawPoint(new Point(250, 150));
    OpenCV::showImage(1500);

    // Demo 2: Add some lines
    std::cout << "2. Adding lines..." << std::endl;
    OpenCV::drawLine(new Point(100, 100), new Point(250, 150));
    OpenCV::drawLine(new Point(150, 150), new Point(200, 100));
    OpenCV::showImage(1500);

    // Demo 3: Clear and draw a simple pattern
    std::cout << "3. Clearing canvas and drawing a pattern..." << std::endl;
    OpenCV::clearCanvas();

    // Draw a simple cross pattern
    OpenCV::drawLine(new Point(250, 150), new Point(250, 350));
    OpenCV::drawLine(new Point(150, 250), new Point(350, 250));
    OpenCV::showImage(1000);

    // Demo 4: Add corner points
    std::cout << "4. Adding corner points..." << std::endl;
    OpenCV::drawPoint(new Point(50, 50)); 
    OpenCV::drawPoint(new Point(450, 50));
    OpenCV::drawPoint(new Point(50, 450));
    OpenCV::drawPoint(new Point(450, 450));
    OpenCV::showImage(1000);

    // Demo 5: Connect the corners
    std::cout << "5. Connecting corners..." << std::endl;
    OpenCV::drawLine(new Point(50, 50), new Point(450, 50));
    OpenCV::drawLine(new Point(450, 50), new Point(450, 450));
    OpenCV::drawLine(new Point(450, 450), new Point(50, 450));
    OpenCV::drawLine(new Point(50, 450), new Point(50, 50));
    OpenCV::showImage(2000);

    // Demo 6: Wait for user input
    std::cout << "6. Press any key to continue..." << std::endl;
    OpenCV::waitForKey();

    // Demo 7: Random lines demonstration
    std::cout << "7. Drawing random lines..." << std::endl;
    OpenCV::clearCanvas();
    for (int i = 0; i < 5; i++)
    {
        OpenCV::drawLine(new Point(rand() % 500, rand() % 500), new Point(rand() % 500, rand() % 500));
        OpenCV::showImage(500);
    }
}