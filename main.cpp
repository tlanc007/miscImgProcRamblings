#include <fmt/printf.h>

#include "image.hpp"
#include "bmpFormat.hpp"

#define DO_TIMER 1

#if DO_TIMER
#include "StopWatch.hpp"

void run_timer(const BMPFormat& bmp)
{
    //    constexpr auto Loops {100000};
    constexpr auto Loops {1000};

    {
        fmt::print ("Timing against {} loops.\n", Loops);
        StopWatch<> sw ("orig");
        for (auto i {0u}; i < Loops; ++i) {
            Image image {bmp};
            image.rotate(180);
        }
    }
}

#endif

int main ()
{
#if 0
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

#  if DO_TIMER
    run_timer (bmp);
#  endif

#endif
}
