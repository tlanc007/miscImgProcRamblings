
#include <algorithm>

#include <gmock/gmock.h>

#include "ImageUtil.hpp"

using namespace ::testing;

TEST (ImageUtilTest, readbmpFile)
{
    constexpr auto ImRows {512};
    constexpr auto ImCols {512};
    constexpr auto bmp {"/Volumes/users/tal/Downloads/vpp/build/examples/lena512.jpg"};

    cv::Mat cvImage {cv::imread(bmp) };

    Image img {copyFromOpenCV(cvImage) };
    ASSERT_EQ(img.rows(), ImRows);
    ASSERT_EQ(img.cols(), ImCols);
}

