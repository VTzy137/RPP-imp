# OpenCV Integration Guide

## Overview

This project includes a comprehensive OpenCV integration for image processing, visualization, and real-time display capabilities. The OpenCV module is designed to support path planning visualization, optimization progress tracking, and general image processing tasks.

## Installation Requirements

Before building the project, ensure OpenCV is installed on your system:

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install libopencv-dev python3-opencv
```

### Fedora/RHEL
```bash
sudo dnf install opencv-devel
```

### macOS (with Homebrew)
```bash
brew install opencv
```

## Building the Project

The CMakeLists.txt has been updated to include OpenCV. Simply build as usual:

```bash
mkdir build && cd build
cmake ..
make
```

This will create two executables:
- `RPP-imp` - Main application
- `opencv_demo` - OpenCV demonstration program

## Module Structure

The OpenCV functionality is organized into several classes and namespaces:

### 1. ImageProcessor Class

Handles basic image processing operations:

```cpp
#include "UI/opencv.hpp"
using namespace OpenCVUI;

// Load and save images
auto image = ImageProcessor::loadImage("input.jpg");
ImageProcessor::saveImage(*image, "output.jpg");

// Basic processing
cv::Mat resized = ImageProcessor::resizeImage(*image, 800, 600);
cv::Mat blurred = ImageProcessor::applyGaussianBlur(*image, 15);
cv::Mat grayscale = ImageProcessor::convertToGrayscale(*image);
cv::Mat edges = ImageProcessor::detectEdges(grayscale);
cv::Mat histogram = ImageProcessor::calculateHistogram(grayscale);
```

### 2. Visualizer Class

Provides visualization utilities for path planning and optimization:

```cpp
// Create a canvas
cv::Mat canvas = Visualizer::createCanvas(800, 600, cv::Scalar(255, 255, 255));

// Draw paths and points
std::vector<Point> path = {Point(10, 10), Point(50, 30), Point(100, 20)};
Visualizer::drawPath(canvas, path, cv::Scalar(0, 255, 0), 2);

std::vector<Point> waypoints = {Point(25, 25), Point(75, 35)};
Visualizer::drawPoints(canvas, waypoints, cv::Scalar(255, 0, 0), 5);

// Create fitness evolution charts
std::vector<double> fitnessHistory = {100, 95, 90, 85, 82, 80};
cv::Mat chart = Visualizer::drawFitnessChart(fitnessHistory, 800, 400);

// Add text labels
Visualizer::addText(canvas, "Path Planning Demo", cv::Point(50, 50));
```

### 3. DisplayManager Class

Manages real-time display windows:

```cpp
DisplayManager display("My Window");
if (display.initialize(800, 600)) {
    // Display images
    display.displayImage(canvas, 1000); // Show for 1 second
    
    // Real-time updates
    for (int i = 0; i < 100; ++i) {
        // Update your visualization
        display.updateDisplay(updatedCanvas);
        
        if (!display.isWindowOpen()) break;
    }
}
```

### 4. Utility Functions

Helper functions for common operations:

```cpp
// Convert between Point and cv::Point2f
cv::Point2f cvPoint = Utils::pointToCvPoint(Point(10, 20));
std::vector<cv::Point2f> cvPoints = Utils::pointsToCvPoints(pathPoints);

// Create color gradients for visualization
cv::Scalar color = Utils::createColorGradient(0.7); // Value between 0-1

// Check OpenCV status
bool isWorking = Utils::isOpenCVInitialized();
std::string info = Utils::getOpenCVInfo();
```

## Usage Examples

### Basic Path Visualization

```cpp
#include "UI/opencv.hpp"
using namespace OpenCVUI;

int main() {
    // Create visualization canvas
    cv::Mat canvas = Visualizer::createCanvas(800, 600);
    
    // Define a path
    std::vector<Point> path;
    for (int i = 0; i < 10; ++i) {
        path.emplace_back(50 + i * 70, 300 + 100 * std::sin(i * 0.5));
    }
    
    // Draw the path
    Visualizer::drawPath(canvas, path, cv::Scalar(0, 255, 0), 3);
    
    // Save result
    ImageProcessor::saveImage(canvas, "path_visualization.png");
    
    return 0;
}
```

### Real-time Optimization Visualization

```cpp
DisplayManager display("Optimization Progress");
display.initialize(800, 600);

std::vector<double> fitnessHistory;
for (int generation = 0; generation < 100; ++generation) {
    // Your optimization algorithm here
    double fitness = runOptimizationStep();
    fitnessHistory.push_back(fitness);
    
    // Update visualization
    cv::Mat chart = Visualizer::drawFitnessChart(fitnessHistory);
    display.updateDisplay(chart);
    
    if (!display.isWindowOpen()) break;
}
```

### Image Processing Pipeline

```cpp
// Load image
auto image = ImageProcessor::loadImage("input.jpg");
if (!image) return -1;

// Processing pipeline
cv::Mat processed = ImageProcessor::resizeImage(*image, 640, 480);
processed = ImageProcessor::applyGaussianBlur(processed, 5);
cv::Mat edges = ImageProcessor::detectEdges(processed);

// Save results
ImageProcessor::saveImage(processed, "processed.jpg");
ImageProcessor::saveImage(edges, "edges.jpg");
```

## Running the Demo

To see all features in action, run the included demo:

```bash
./opencv_demo
```

This demo will:
1. Create path planning visualizations
2. Generate optimization progress charts
3. Demonstrate image processing capabilities
4. Show real-time animation (if display is available)

## Integration with Your Algorithm

### For Path Planning Algorithms

```cpp
// In your path planning function
std::vector<Point> generatePath() {
    // Your algorithm implementation
    std::vector<Point> path;
    // ... generate path ...
    return path;
}

// Visualization
cv::Mat canvas = Visualizer::createCanvas(800, 600);
auto path = generatePath();
Visualizer::drawPath(canvas, path, cv::Scalar(0, 255, 0));
ImageProcessor::saveImage(canvas, "generated_path.png");
```

### For Optimization Algorithms

```cpp
class OptimizationAlgorithm {
private:
    std::vector<double> fitnessHistory;
    DisplayManager display{"Optimization"};
    
public:
    void run() {
        display.initialize();
        
        for (int gen = 0; gen < maxGenerations; ++gen) {
            double fitness = optimizationStep();
            fitnessHistory.push_back(fitness);
            
            // Update visualization every 10 generations
            if (gen % 10 == 0) {
                cv::Mat chart = Visualizer::drawFitnessChart(fitnessHistory);
                display.updateDisplay(chart);
            }
        }
    }
};
```

## Performance Considerations

1. **Memory Management**: All functions use RAII principles and smart pointers where appropriate
2. **Real-time Performance**: Use `DisplayManager::updateDisplay()` for real-time applications
3. **Thread Safety**: OpenCV operations are generally not thread-safe; use proper synchronization if needed
4. **Error Handling**: All functions include proper error checking and validation

## Troubleshooting

### Common Issues

1. **OpenCV not found during build**:
   - Ensure OpenCV development packages are installed
   - Check that `pkg-config --modversion opencv4` returns a version number

2. **Display not working**:
   - In headless environments, display functions will fail gracefully
   - Use image saving functions instead for server deployments

3. **Performance issues**:
   - Use appropriate image sizes for your application
   - Consider using threading for CPU-intensive operations

### Debug Build

For debugging OpenCV issues, build with debug information:

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

This will enable additional error checking and debugging symbols. 