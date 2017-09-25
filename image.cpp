#include <algorithm>
#include <cmath>

#include "image.hpp"

#include <fmt/printf.h>

Image::Image (Col_t numCols_, Row_t numRows_, size_t maxGrayLevel_)
: _pixCountX {numCols_},
_pixCountY {numRows_},
_maxGrayLevel {maxGrayLevel_},
_pixels {PixelContainer (numRows_ * numCols_, 0) }
{ }

Image::Image (const std::string& fname_)
{
    // need better i/o
    readImage (fname_);
}

Image::Image (const BMPFormat& bmp)
: _pixCountX {bmp.nCols},
_pixCountY {bmp.nRows},
_maxGrayLevel {127},
_pixels {bmp.pixels}
{ }

void Image::copyToBmp(BMPFormat& bmp)
{
    // a bit overslimlified
    bmp.pixels = _pixels;
}

void Image::buildDummyImage()
{
    constexpr auto Modulo {128};
    unsigned char val {0};
    std::for_each (std::begin (_pixels), std::end (_pixels), [&val] (auto& v) {
        ++val;
        val %= Modulo;
        v = val;
    } );
}

void Image::dumpImage() const
{
#if 0
    std::for_each (std::begin (_pixels), std::end (_pixels), [] (auto v) {
        fmt::print ("{} ", v);
    } );
#else
    auto val {_pixels.data () };
    for (auto y {0u}; y < _pixCountY; ++y) {
        for (auto x {0u}; x < _pixCountX; ++x) {
            fmt::print ("{} ", *val++);
        }
        fmt::print ("\n");
    }
#endif
    fmt::print ("\n");

}
void Image::readImage(const std::string& fname_)
{
    std::ifstream ifp {fname_, std::ios::in | std::ios::binary};

    if (!ifp) {
        fmt::print ("Can't read image file {}\n", fname_);
        std::terminate ();
    }

    constexpr auto HeaderSz {100u};
    char header[HeaderSz];
    char* ptr;

    // magic number
    ifp.getline(header,HeaderSz,'\n');
    if ( (header[0]!=80) || (header[1]!=53) )     //if not P5
    {
        fmt::print ("Image {} is not PGM\n", fname_);
        std::terminate ();
    }

    do {
        ifp.getline(header,HeaderSz,'\n');

    } while (header[0] == '#');

    _pixCountX = std::strtol (header, &ptr, 0);
    _pixCountY = std::strtol (header, &ptr, 0); // this looks wrong

    ifp.getline (header, HeaderSz, '\n');
    _maxGrayLevel = std::strtol (header, &ptr, 0);

    auto size {_pixCountY * _pixCountX};
    _pixels.reserve (size);
    ifp.read (reinterpret_cast <char*> (_pixels.data () ), size * sizeof (unsigned char) );

    ifp.close ();

}

// rotation based on center of image
void Image::rotate(int degrees_)
{
    constexpr auto PI {3.141593};
    constexpr auto Rad {PI / 180.0};

    Image tmp {_pixCountX, _pixCountY, _maxGrayLevel};
    const auto radians {degrees_* Rad};
    const auto cr {cos (radians) };
    const auto sr {sin (radians) };

    // center of image
    const double centerY {(_pixCountY-1) / 2.0};
    const double centerX {(_pixCountX-1) / 2.0};

    auto roundCastLong = [] (auto newVal, auto center) {
        return static_cast <long> (round (newVal + center) );
    };

    for (auto y {0u}; y < _pixCountY; ++y) {
        for (auto x {0u}; x < _pixCountX; ++x) {
            auto xPos {x - centerX};
            auto yPos {y - centerY};

            auto xnew {xPos * cr - yPos * sr };
            auto ynew {yPos * cr + xPos * sr };

            auto x1 {roundCastLong (xnew, centerX) };
            auto y1 {roundCastLong (ynew, centerY) };

            if (inBounds(y1, x1) ) {
                tmp.setVal(x1, y1, at(x, y) );
            }
            else {
                fmt::print ("{},{} out of bounds\n", x1, y1);
            }
        }
    }
    std::swap (_pixels, tmp._pixels);

}

size_t Image::yOffset (Row_t y_) const
{
    assert (y_ < _pixCountY && "range error");
    return _pixCountX * y_;
}

unsigned Image::at (Col_t x_, Row_t y_) const
{
    assert (x_ < _pixCountX && y_ < _pixCountY && "range error");
    return _pixels[yOffset(y_) + x_];
}

void Image::setVal(Col_t x_, Row_t y_, unsigned int val)
{
    assert (x_ < _pixCountX && y_ < _pixCountY && "range error");
    _pixels [yOffset(y_) + x_] = val;
}

bool Image::inBounds(Col_t col_, Row_t row_) const
{
    return col_ < _pixCountY && row_ < _pixCountX;
}
