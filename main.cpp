#include "image.hpp"

int main ()
{
    Image image {3, 3, 128};
    image.buildDummyImage();
    image.dumpImage();
    image.rotate(180);
    image.dumpImage();

}
