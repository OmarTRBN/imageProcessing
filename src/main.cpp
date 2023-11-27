#include <iostream>
#include "OmarImage.hpp"
#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[])
{
    // OmarImage image("test.jpg");

    // image.write("new.png");

    // cout << image.channels << endl;
    // cout << image.h << endl;
    // cout << image.w << endl;
    // cout << image.size << endl;


    // OmarImage blank(100, 100, 1);
    // bool success = blank.write("blank.jpg");
    // std::cout << success << endl;

    // OmarImage copy = image;
    // for (int i = 0; i < copy.h*copy.w; ++i)
    // {
    //     copy.data[i] = 255;
    // }
    // success = copy.write("copy.jpg");
    // std::cout << success << endl;
    OmarImage grayDog("../rgbFlag.png");
    grayDog.colorMask(0, 1, 0.0);
    grayDog.write("../greenMaskFlag.jpg");

    OmarImage wqDog("../rgbFlag.png");
    wqDog.colorMask(0, 0, 1);
    wqDog.write("../blueMaskFlag.jpg");

    return 0;
}
