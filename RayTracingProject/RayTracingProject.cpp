// RayTracingProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "commonItems.h"

#include "hittable.h"
#include "hittableList.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

/*
color rayColor(const ray& r, const hittable& world) {

    hitRecord rec;
    if (world.hit(r, interval(0, infinity), rec)) { return 0.5 * (rec.normal + color(1, 1, 1)); }


    vec3 unitDirection = unitVector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
} //end rayColor stub
*/


int main()
{
    //world
    hittableList world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;

    cam.render(world);

    /*
    //image

    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;


    //calculate the image height and ensure it is at least 1
    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;


    


    //camera
    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    auto cameraCenter = point3(0, 0, 0);


    //calculate the vectors across the horizontal and across the vertical viewport edges
    auto viewportU = vec3(viewportWidth, 0, 0);
    auto viewportV = vec3(0, -viewportHeight, 0);


    //calculate the horizontal and vertical delta vectors from pixel to pixel
    auto pixelDeltaU = viewportU / imageWidth;
    auto pixelDeltaV = viewportV / imageHeight;

    
    //calculate the position of the upper left pixel
    auto viewportUpperLeft = cameraCenter - vec3(0, 0, focalLength)
                            - (viewportU / 2) - (viewportV / 2);
    auto pixel00Location = viewportUpperLeft + (0.5 * (pixelDeltaU + pixelDeltaV));


    //render

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int i = 0; i < imageHeight; i++) {
        std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
        for (int j = 0; j < imageWidth; j++) {
            auto pixelCenter = pixel00Location + (j * pixelDeltaU) + (i * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            ray r(cameraCenter, rayDirection);

            color pixelColor = rayColor(r, world);
            writeColor(std::cout, pixelColor);
        }

    }

    std::clog << "\rDone.                      \n";
    */

}

