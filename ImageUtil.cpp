
#include <algorithm>

#include "ImageUtil.hpp"

// Todo: this only works for 8bit greyscale!
Image copyFromOpenCV (const cv::Mat& cvImage)
{
    constexpr auto bits {8u};
    Image img {cvImage.cols, cvImage.rows, bits, static_cast<Channels> (cvImage.channels() ) };

    PixelContainer pixels {};
    const auto containerSize {img.pixelContainer().size()};
    pixels.reserve(containerSize);
    auto cvData {cvImage.data};
    for (auto i {0u}; i < containerSize; ++i) {
        pixels.emplace_back(*cvData++);
    }

    img.pixels(pixels);

    return img;
}

cv::Mat copyToOpenCV (const Image& im)
{
    cv::Mat m = cv::Mat_<unsigned char> (
                                         static_cast<int> (im.rows () ),
                                         static_cast<int> (im.cols() ) );

    auto cvData {m.data};
    auto pixels {im.pixelContainer() };

    std::for_each (std::begin (pixels), std::end (pixels), [&cvData] (auto& e) {
        *cvData++ = e;
    } );


    return m;
}

bool compareImageWithCVImage (IMPixel& imPixel, const CVPixel& cvPixel )
{
    /* fmt::print ("imPixel ({}, {}, {}) ", *imPixel, *(imPixel+1), *(imPixel+2) );
    fmt::print ("cvPixel(xyz) ({}, {}, {})\n",
                cvPixel.x, cvPixel.y, cvPixel.z); */
    return *imPixel == cvPixel.x;
}
