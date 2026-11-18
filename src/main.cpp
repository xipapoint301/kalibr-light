#include <ceres/ceres.h>
#include <Eigen/Core>
#include <opencv2/core.hpp>
#include <sophus/se3.hpp>

#include <iostream>

int main() {
  Eigen::Vector3d v(1, 2, 3);
  Sophus::SE3d T(Sophus::SO3d::exp(Eigen::Vector3d(0, 0, 0.1)), v);
  cv::Mat m = cv::Mat::eye(3, 3, CV_64F);

  std::cout << "Ceres " << CERES_VERSION_STRING << "\n"
            << "OpenCV " << CV_VERSION << "\n"
            << "T =\n" << T.matrix() << "\n"
            << "cv::Mat =\n" << m << std::endl;
  return 0;
}
