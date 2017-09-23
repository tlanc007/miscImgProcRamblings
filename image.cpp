#include <algorithm>

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

size_t Image::yOffset (Row_t y_) const
{
    assert (y_ < _pixCountY && "range error");
    return _pixCountX * y_;
}

int Image::at (Row_t x_, Col_t y_) const
{
    assert (x_ < _pixCountX && y_ < _pixCountY && "range error");
    return yOffset(y_) + x_;
}

bool Image::inBounds(Row_t row_, Col_t col_) const
{
    return row_ < _pixCountX && col_ < _pixCountY;
}
