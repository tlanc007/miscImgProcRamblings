
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

TEST (ImageUtilTest, writebmpFile)
{
    constexpr auto Rows {128};
    constexpr auto Cols {128};
    constexpr auto Bits {8};
    constexpr auto Channel {1u};
    constexpr unsigned char PixVal {255};
    constexpr auto WritePath {"/tmp/imageUtilFileTest.ppm"};

    const PixelContainer pcData (Rows*Cols, PixVal);
    Image img {Cols, Rows, Bits, Channel};
    img.pixels(pcData);

    cv::imwrite (WritePath, copyToOpenCV(img));

    // verify written image by reading back in
    cv::Mat fromDisk {cv::imread (WritePath) };

    ASSERT_EQ (Cols, fromDisk.cols);
    ASSERT_EQ (Rows, fromDisk.rows);

    auto matDiskData {fromDisk.data };
    auto expectedData {std::begin (pcData) };
    // only checking first row
    for (auto i {0u}; i < Cols; ++i) {
        ASSERT_EQ(*matDiskData++, *expectedData++);
    }
}

