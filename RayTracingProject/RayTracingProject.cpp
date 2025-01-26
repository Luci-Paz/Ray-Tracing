// RayTracingProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
            auto r = double(j) / (imageWidth - 1);
            auto g = 0.0;
            auto b = double(i) / (imageWidth - 1);

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }

    }

    std::clog << "\rDone.                      \n";

}

