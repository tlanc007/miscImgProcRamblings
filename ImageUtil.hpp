#ifndef IMAGE_UTIL_HPP
#define IMAGE_UTIL_HPP

#include <opencv/cv.hpp>

#include "Image.hpp"

Image copyFromOpenCV (const cv::Mat& cvImage);
cv::Mat copyToOpenCV (const Image& image);


#endif // IMAGE_UTIL_HPP
