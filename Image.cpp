
#include <cassert>

#include "Image.hpp"

void Image::pixels (PixelContainer pixels_)
{
    // todo: need to account for bitspp and channels
    assert (pixels_.size() == _pixels.size () && "image data doesn't match size");
    _pixels = pixels_;
}

PixelContainer Image::pixelContainer() const
{
    return _pixels;
}

void Image::dump () const
{
    auto pix {_pixels.data () };
    for (auto y {0u}; y < _pixelsY; ++y) {
        for (auto x {0u}; x < _pixelsX; ++x) {
            fmt::print ("{} ", *pix++);
        }
        fmt::print ("\n");
    }
    fmt::print ("\n");
}

void Image::buildDummyImage8BitGray ()
{
    constexpr auto Modulo {127};
    unsigned char val {0u};
    std::for_each (std::begin (_pixels), std::end (_pixels), [&val] (auto& v) {
        ++val;
        val %= Modulo;
        v = val;
    } );
}
