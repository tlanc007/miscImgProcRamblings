
#include <algorithm>

#include <gmock/gmock.h>

#include "ImageUtil.hpp"

using namespace ::testing;

TEST (ImageUtilFileTest, readbmpFile)
{
    constexpr auto ImRows {512};
    constexpr auto ImCols {512};
    constexpr auto bmp {"/Volumes/users/tal/Downloads/vpp/build/examples/lena512.jpg"};

    cv::Mat cvImage {cv::imread(bmp) };

    // Todo: Not exactly checking image data
    Image img {copyFromOpenCV(cvImage) };
    ASSERT_EQ(img.rows(), ImRows);
    ASSERT_EQ(img.cols(), ImCols);
}

TEST (ImageUtilFileTest, writebmpFile)
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

class ImageFileUtilRead: public Test
{
public:
    cv::Mat cvImage {};
    Image img { };

    void SetUp() {
        buildCVImage();
    }

private:
    void buildCVImage ();

#if 0
    // compiler has linking issues
    static constexpr auto ImRows {32};
    static constexpr auto ImCols {32};
#else
    static const int ImRows;
    static const int ImCols;
#endif
};

const int ImageFileUtilRead::ImRows {32};
const int ImageFileUtilRead::ImCols {32};

void ImageFileUtilRead::buildCVImage () {
    int sizes[] {ImCols, ImRows};
    cv::Mat rgb {2, sizes, CV_8UC3};
    //fmt::print (" ({}, {}): mat dims {} chans {} depth {} total {}\n", rgb.rows, rgb.cols, rgb.dims, rgb.channels(), rgb.depth(), rgb.total() );

    ASSERT_EQ(ImRows, rgb.rows);
    ASSERT_EQ(ImCols, rgb.cols);

    using cvPixel = cv::Point3_<uint8_t>;
    for (auto y {0u}; y < ImRows; ++y) {
        uint8_t r {100};
        uint8_t g {50};
        uint8_t b {200};
        //cvPixel* colPtr {rgb.ptr <cvPixel> (0, y) }; // docs wrong
        cvPixel* colPtr {rgb.ptr <cvPixel> (y, 0) };
        const auto colPtrEnd {colPtr + ImCols};
        auto x {0u};
        for (; colPtr != colPtrEnd; ++colPtr, ++r, ++g, ++b, ++x) {
            colPtr->x = r;
            colPtr->y = g;
            colPtr->z = b;
            if (colPtr == colPtrEnd-1)
                ; //fmt::print ("({}, {}): {}, {}, {}\n", x, y, colPtr->x, colPtr->y, colPtr->z );

        }
    }
    cv::imwrite("rgb.tif", rgb);

    // cheating rather than reading the image just reusing rgb
    cvImage = rgb;
    img = copyFromOpenCV(cvImage);
}

TEST_F(ImageFileUtilRead, read8bitRGBImg)
{

    ASSERT_EQ(cvImage.channels(), img.channels () );



}



// add tests for alternate pixel sizes (types)
