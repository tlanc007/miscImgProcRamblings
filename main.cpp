#include "image.hpp"

int main ()
{
    Image image {3, 3, 128};
    image.buildDummyImage();
    image.dumpImage();
}
