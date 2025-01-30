// RayTracingProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>


double hitSphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - (radius * radius);
    auto discriminant = (b * b) - (4 * a * c);
    
    
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    } //end if-else

} //end hitSphere


color rayColor(const ray& r) {

    auto t = (hitSphere(point3(0, 0, -1), 0.5, r));
        if (t > 0.0) {
            vec3 normal = unitVector(r.at(t) - vec3(0, 0, -1));
            return 0.5 * color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
        }


    vec3 unitDirection = unitVector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
} //end rayColor stub



int main()
{
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

            color pixelColor = rayColor(r);
            writeColor(std::cout, pixelColor);
        }

    }

    std::clog << "\rDone.                      \n";

}

