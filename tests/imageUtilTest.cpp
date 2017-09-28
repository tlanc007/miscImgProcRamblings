#include <vector>

#include <gmock/gmock.h>

#include "ImageUtil.hpp"

using namespace ::testing;

TEST (ImageUtilTest, create2x2ImageFromOpenCVMat)
{
    std::vector <unsigned char> expected {1, 2, 3, 4};
    constexpr auto Rows {2u};
    constexpr auto Cols {2u};
    cv::Mat cvImage = (cv::Mat_<unsigned char> (Rows, Cols) << 1, 2, 3, 4);

    Image img {copyFromOpenCV(cvImage) };
    ASSERT_EQ (expected, img.pixelContainer () );
}
