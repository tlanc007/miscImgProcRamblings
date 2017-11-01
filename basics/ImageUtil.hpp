#ifndef IMAGE_UTIL_HPP
#define IMAGE_UTIL_HPP

#include <opencv/cv.hpp>

#include "Image.hpp"

using CVPixel = cv::Point3_<uint8_t>;
using IMPixel = uint8_t*;

Image copyFromOpenCV (const cv::Mat& cvImage);
cv::Mat copyToOpenCV (const Image& image);
bool compareImageWithCVImage (IMPixel& imPixel, const CVPixel& cvPixel );

#endif // IMAGE_UTIL_HPP
