#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    int num = -1;
    cv::Mat img = cv::imread("/home/icarus/img_proc_intro/opencv_example/img/7.png");
    // cv::resize(img, img, cv::Size(100, 20));
    cv::Mat original_img = img;
    cv::cvtColor(img, img, CV_BGR2GRAY);
    cv::GaussianBlur(img, img, cv::Size(3, 3), cv::BORDER_DEFAULT);
    cv::Canny(img, img, 100, 150, 3, false);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    cv::Rect rect = cv::boundingRect(contours[0]);
    // cv::rectangle(original, rect, cv::Scalar(255, 0, 0));
    cv::Mat cropped_img = original_img(cv::Range(rect.y - 1, rect.y + 1 + rect.height), cv::Range(rect.x - 1, rect.x + 1 + rect.width));
    // cv::threshold(cropped_img, cropped_img, 80, 100, CV_THRESH_TOZERO);
    cv::Mat tmp_img;
    std::vector<cv::Point> corners;
    cv::cvtColor(cropped_img, tmp_img, CV_BGR2GRAY);
    cv::goodFeaturesToTrack(tmp_img, corners, 20, 0.1, 2);
    for (auto corner : corners)
    {
        cv::circle(cropped_img, corner, 2, cv::Scalar(0, 255, 0));
    }
    cv::resize(cropped_img, cropped_img, cv::Size(400, 400));
    cv::imshow("img", cropped_img);
    if (corners.size() == 7)
        num = 7;
    std::cout << "The number is: " << num << std::endl;
    cv::waitKey();
    return 0;
}