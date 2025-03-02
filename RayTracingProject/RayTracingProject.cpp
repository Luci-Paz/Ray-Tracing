// RayTracingProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "commonItems.h"

//my class includes
#include "hittable.h"
#include "hittableList.h"
#include "sphere.h"
#include "camera.h"

//opencv includes
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <fstream>

using namespace cv;

int main()
{
    //world
    hittableList world;
    world.add(make_shared<sphere>(point3(0, 0, -10), 0.5));
    world.add(make_shared<sphere>(point3(-1, 0, -1), 0.75));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 200;
    cam.samplesPerPixel = 100;
    cam.maxDepth = 50;

    cam.render(world);

    
    //display image
    Mat displayImage = imread("renderedImage.ppm");
    
    //error handling
    if (displayImage.empty()) {
        std::cout << "Image file not found" << std::endl;
        std::cin.get();
        return -1;
    } //end if

    imshow("Rendered Image", displayImage);
    waitKey(0);
    return 0; 
}

