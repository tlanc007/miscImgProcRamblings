#include <gmock/gmock.h>

#include "Image.hpp"

using namespace ::testing;

constexpr auto PixelsX3 {3u};
constexpr auto PixelsY3 {3u};
constexpr auto BitDepth {8u};
constexpr auto Chanels {1u};

class ImageBasicTest: public Test
{
public:
    Image image {PixelsX3, PixelsY3, BitDepth, Chanels};

};

TEST_F (ImageBasicTest, ConfirmDummy8BitGray)
{
    const PixelContainer expected {1, 2, 3, 4, 5, 6, 7, 8, 9};
    image.buildDummyImage8BitGray ();

    ASSERT_EQ (expected, image.pixelContainer () );
}

