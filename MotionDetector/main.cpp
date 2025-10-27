#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap(0); 

    // Cria o objeto de subtração de fundo
    cv::Ptr<cv::BackgroundSubtractorMOG2> pBackSub = cv::createBackgroundSubtractorMOG2();
    cv::Mat frame, fgMask;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // Aplica o algoritmo de subtração de fundo
        pBackSub->apply(frame, fgMask);

        // Opcional: aplica um filtro para remover ruído
        cv::erode(fgMask, fgMask, cv::Mat());
        cv::dilate(fgMask, fgMask, cv::Mat());
        
        cv::imshow("Frame Original", frame);
        cv::imshow("Máscara de Movimento (Foreground)", fgMask);

        if (cv::waitKey(30) == 27) break; 
    }
    return 0;
}