#include <opencv2/opencv.hpp>
#include <iostream>

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;

int main() {
    std::cout << "/* Starting */" << std::endl;
    cv::Mat image = cv::imread("blackhole.jpg");
    if (image.empty()) {
        std::cerr << "Error: Could not open image file." << std::endl;
        return -1;
    }

    // Create a window with fixed size (not resizable)
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(WINDOW_WIDTH, WINDOW_HEIGHT));

    cv::namedWindow("Display Image", cv::WINDOW_NORMAL);
    cv::resizeWindow("Display Image", WINDOW_WIDTH, WINDOW_HEIGHT);

    cv::imshow("Display Image", resizedImage);
    cv::waitKey(0);
    return 0;
}