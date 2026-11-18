#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>

namespace kalibr_light
{
    class AprilGridDetector
    {
    public:
        AprilGridDetector()
        {
            parameters_->cornerRefinementMethod = cv::aruco::CORNER_REFINE_APRILTAG;
            parameters_->cornerRefinementWinSize = 5;
            parameters_->cornerRefinementMaxIterations = 30;
            parameters_->cornerRefinementMinAccuracy = 0.01;
        };
        void detect(cv::Mat image)
        {
            auto gray = to_gray(image);
            cv::aruco::detectMarkers(gray, dictionary_, markerCorners, markerIds);
        };
        
    private:
        cv::Ptr<cv::aruco::Dictionary> dictionary_ = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
        cv::Ptr<cv::aruco::DetectorParameters> parameters_ = cv::aruco::DetectorParameters::create();
        cv::Mat out_;
        std::vector<int> markerIds;
        std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
        cv::Mat to_gray(cv::Mat image) {
            cv::Mat grayImage; 
            cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
            return grayImage;
        };
    };
}