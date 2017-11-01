#include <algorithm>

#include "bmpFormat.hpp"

long getImageInfo(FILE* inputFile, long offset, int numberOfChars)
{
    unsigned char *ptrC;
    long value = 0L, temp;
    unsigned char dummy;
    int i;

    dummy = '0';
    ptrC = &dummy;

    //position the file pointer to the desired offset.
    fseek(inputFile, offset, SEEK_SET);

    //read the bytes into values (one byte at a time).
    for(i=0; i<numberOfChars; i++)
    {
        fread(ptrC,sizeof(char),1,inputFile);
        temp = *ptrC;
        value = (long) (value + (temp<<(8*i)));
    }

    return(value);
}

bool BMPFormat::verifyFormat (FILE* bmpInput)
{
    fseek(bmpInput, 0L, SEEK_SET);

    char signature[2];  //magic

    //read First two characters of the input file.
    for(auto i=0; i<2; i++)
    {
        signature[i] = (char)getImageInfo(bmpInput,i,1);
    }

    return signature[0] == 'B' && signature[1] == 'M';
}

void BMPFormat::readPixelsFromFile(FILE *bmpInput, long rasterOffset)
{
    auto pix {pixels.data () };
    for (auto i {0u}; i < nCols * nRows; ++i, ++pix) {
        pixels.emplace_back ( getImageInfo(bmpInput, rasterOffset + i, 1) );
    }
}

void BMPFormat::readFile(const std::string &fname)
{
    FILE* bmpInput;

    if ( (bmpInput = fopen (fname.c_str (), "rb" ) ) == nullptr) {
        throw std::runtime_error ("couldn't open file for reading");
    }

    fseek(bmpInput, 0L, SEEK_SET);
    if (!verifyFormat(bmpInput) ) throw std::runtime_error ("image file not BMP");

    auto nBits {getImageInfo(bmpInput, 28, 2) };
    auto rasterOffset {getImageInfo(bmpInput,10,4) };
    auto fileSize {getImageInfo(bmpInput,2,4) };
    nCols = getImageInfo(bmpInput,18,4);
    nRows = getImageInfo(bmpInput,22,4);

    header.reserve(rasterOffset);
    for (auto i {0u}; i < rasterOffset; ++i) {
        //*headerData = static_cast <char> (getImageInfo(bmpInput, i, 1) );
        header.emplace_back(static_cast <char> (getImageInfo(bmpInput, i, 1) ) );
    }

    pixels.reserve (nCols * nRows);
    readPixelsFromFile(bmpInput, rasterOffset);

    fclose (bmpInput);
}

void BMPFormat::writeFile(const std::string &fname)
{
    FILE *bmpOutput {fopen (fname.c_str (), "w+") };

    if (bmpOutput == nullptr) throw std::runtime_error ("unable to create file for writing");

    std::for_each (std::begin (header), std::end (header), [&bmpOutput] (const auto val) {
        fputc (val, bmpOutput);
    } );

    std::for_each (std::begin (pixels), std::end (pixels), [&bmpOutput] (const auto val) {
        fputc (val, bmpOutput);
    } );

    fclose (bmpOutput);
}
