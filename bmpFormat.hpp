// simple code to read/write bmp file.

#ifndef BMP_FORMAT_HPP
#define BMP_FORMAT_HPP 1

#include <memory>
#include <string>
#include <vector>
#include <stdio.h>

using VecChar = std::vector <char>;

long getImageInfo(FILE* inputFile, long offset, int numberOfChars);

struct BMPFormat
{
    BMPFormat (size_t cols, size_t rows, size_t colors)
    : nCols {cols},
    nRows {rows},
    nColors {colors},
    pixels (cols * rows, 0)
    { }

    BMPFormat (const std::string& fname) {readFile (fname); }

    void readFile (const std::string& fname);
    void writeFile (const std::string& fname);

    bool verifyFormat (FILE* bmpInput);
    void readPixelsFromFile (FILE* bmpInput, long rasterOffset);


    size_t nCols;
    size_t nRows;
    size_t nColors;
    VecChar pixels;
    VecChar header {};
};

#endif
