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
    std::for_each (std::begin (_pixels), std::end (_pixels), [] (auto v) {
        fmt::print ("{} ", v);
    } );

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
    auto radians {degrees_* Rad};

    // center of image
    auto r0 {_pixCountY / 2};
    auto c0 {_pixCountX / 2};

    for (auto r {0u}; r < _pixCountY; ++r) {
        for (auto c {0u}; c < _pixCountX; ++c) {
            auto y0 {yOffset(r0) };
            auto y {yOffset(r) };
            auto r1 {y0 + ( (y - y0) * cos (radians) - ((c - c0) * sin (radians) ) ) };
            auto c1 {c0 + ( (y - y0) * sin (radians) + ((c - c0) * cos (radians) ) ) };

            if (inBounds(r1, c1) ) {
                tmp.setVal(c1, r1, at(c, r) );
            }
            else {
                fmt::print ("{},{} out of bounds\n", r1, c1);
            }
        }
    }
    //_pixels.swap (tmp._pixels);
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

bool Image::inBounds(Row_t row_, Col_t col_) const
{
    return row_ < _pixCountX && col_ < _pixCountY;
}
