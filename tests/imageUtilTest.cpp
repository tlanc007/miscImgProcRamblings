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

using CVPixel = cv::Point3_<uint8_t>;

class ImageUtilChannelsTest: public Test
{
public:
    cv::Mat cvImage {};
    Image img {};

    void SetUp () {
        buildCVImage();
    }

private:
    void buildCVImage ();



};

void ImageUtilChannelsTest::buildCVImage()
{
    constexpr auto Red {50};
    constexpr auto Green {100};
    constexpr auto Blue {200};
    int sizes[] {2, 2};
    cv::Mat rgb {2, sizes, CV_8UC3};

    for (auto &p: cv::Mat_<CVPixel> (rgb) ) {
        p.x = Red;
        p.y = Green;
        p.z = Blue;
    }

    cvImage = rgb;
    img = copyFromOpenCV(cvImage);
}

TEST_F (ImageUtilChannelsTest, checkRGB)
{
    // Todo: need an Image pointer call
    PixelContainer imgPixels {img.pixelContainer() };
    auto imgPixData {imgPixels.data () };
    for (auto r {0u}; r < cvImage.rows; ++r) {
        auto cvPtr {cvImage.ptr <CVPixel> (r, 0) };
        const auto cvPtrEnd {cvPtr + cvImage.cols};
        for (; cvPtr != cvPtrEnd; ++cvPtr) {
            ASSERT_TRUE (compareImageWithCVImage (imgPixData, *cvPtr ) );
            imgPixData += 3;
        }
    }
}
