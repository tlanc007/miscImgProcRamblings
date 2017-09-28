#include "ImageUtil.hpp"

// Todo: this only works for 8bit greyscale!
Image copyFromOpenCV (const cv::Mat& cvImage)
{
    constexpr auto bits {8u};
    constexpr auto channel {1u};
    Image img {cvImage.cols, cvImage.rows, bits, channel};

    PixelContainer pixels {};
    const auto containerSize {cvImage.cols * cvImage.rows};
    pixels.reserve(containerSize);
    auto cvData {cvImage.data};
    for (auto i {0u}; i < containerSize; ++i) {
        pixels.emplace_back(*cvData++);
    }

    img.pixels(pixels);
    
    return img;
}
