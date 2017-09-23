#ifndef IMAGE_H
#define IMAGE_H

#include <cassert>
//#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//#include <gsl/gsl>

// what about type ie uint8, 16, 32?
using PixelContainer = std::vector <unsigned char>;
using Row_t = size_t;
using Col_t = size_t;

class Image
{
public:
    explicit Image (Col_t numCols_, Row_t numRows_, size_t maxGrayLevel_);
    explicit Image (const std::string& fname);

    int at (Col_t x_, Row_t y_) const;
    void setVal (Row_t x_, Col_t, unsigned val);

    bool inBounds (Row_t row_, Col_t col_) const;
    void buildDummyImage ();
    void dumpImage () const;

private:
    void readImage (const std::string& fname);
    inline size_t yOffset (Col_t y_) const;

    Col_t _pixCountX;
    Row_t _pixCountY;
    size_t _maxGrayLevel;
    PixelContainer _pixels {};
};

#endif // IMAGE_H
