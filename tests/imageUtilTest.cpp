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

TEST (ImageUtilTest, create2x2CVMatFromImage)
{
    constexpr auto Rows {2u};
    constexpr auto Cols {2u};
    constexpr auto bits {8u};
    constexpr auto channel {1u};
    Image img (Cols, Rows, bits, channel);
    const PixelContainer imgData {4, 3, 2, 1};
    img.pixels(imgData);

    cv::Mat cvImage {copyToOpenCV (img) };
    Image backFrom {copyFromOpenCV(cvImage) };

    ASSERT_EQ (Rows, backFrom.rows() ); // just to make sure
    ASSERT_EQ (Cols, backFrom.cols() ); // just to make sure
    ASSERT_EQ (imgData, backFrom.pixelContainer() );
}
