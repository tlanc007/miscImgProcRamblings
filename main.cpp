#include "image.hpp"
#include "bmpFormat.hpp"

int main ()
{
#if 1
    Image image {3, 3, 128};
    image.buildDummyImage();
    image.dumpImage();
    image.rotate(180);
    image.dumpImage();
#else
    BMPFormat bmp {"/Volumes/users/tal/Documents/GoogleDrive/Docs/Programming/imageProc/filters/lena512.bmp"};
    Image image {bmp};
    image.rotate(180);
    image.copyToBmp(bmp);

    bmp.writeFile ("/Volumes/users/tal/Documents/GoogleDrive/Docs/Programming/imageProc/filters/lout_512.bmp");

#endif
}
