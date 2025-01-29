// RayTracingProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "vec3.h"
#include "color.h"
#include <iostream>

int main()
{
    //image

    int imageWidth = 256;
    int imageHeight = 256;


    //render

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int i = 0; i < imageHeight; i++) {
        std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
        for (int j = 0; j < imageWidth; j++) {
            auto pixelColor = color(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0);
            writeColor(std::cout, pixelColor);
        }

    }

    std::clog << "\rDone.                      \n";

}

