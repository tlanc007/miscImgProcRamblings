#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>

#include <gsl/gsl>
#include <fmt/printf.h>

// doesn't do any type checking, just a visual cue for the user.
using Cols = int;
using Rows = int;
using BitsPP = size_t;
using Channels = size_t;

/* of limited use as only accounts for greyscale 8bit image
   perhaps a template of the proper bitdepth and channels or a template class
 */
using PixelContainer = std::vector <unsigned char>;

class Image
{
public:
    Image (Cols pixelsX_, Rows pixelsY_, BitsPP bitsPP_, Channels channels_)
    : _pixelsX {pixelsX_},
    _pixelsY {pixelsY_},
    _bitsPerPixel {bitsPP_},
    _channels {channels_},
    _pixels (pixelsX_ * pixelsY_, 0) // Todo: this needs to account for bits
    { }
    
    void pixels (PixelContainer pixels_);
    PixelContainer pixelContainer () const;

    size_t rows () const { return _pixelsY; }
    size_t cols () const { return _pixelsX; }

    void dump () const;
    void buildDummyImage8BitGray ();
    
private:
    Cols _pixelsX;
    Rows _pixelsY;
    size_t _bitsPerPixel {8};
    size_t _channels {1};
    PixelContainer _pixels;
};

#endif // IMAGE_HPP

