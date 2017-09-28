
#include <algorithm>

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

cv::Mat copyToOpenCV (const Image& im)
{

#if 0
    // for some reason creates a 3,1 rather than 2,2
    cv::Mat m {
        static_cast<int> (im.rows () ),
        static_cast<int> (im.cols() ), CV_8UC1 // Todo: hardwired
    };

    fmt::print ("im rows {} sc_int {}\n", im.rows(), static_cast<int>(im.rows() ) );
    fmt::print ("im cols {} sc_int {}\n", im.cols(), static_cast<int>(im.cols() ) );
    fmt::print ("M rows {} cols {}\n", m.rows, m.cols);
#else
    cv::Mat m = cv::Mat_<unsigned char> (
                                         static_cast<int> (im.rows () ),
                                         static_cast<int> (im.cols() ) );
#endif

    auto cvData {m.data};
    auto pixels {im.pixelContainer() };

    std::for_each (std::begin (pixels), std::end (pixels), [&cvData] (auto& e) {
        *cvData++ = e;
    } );


    return m;
}
