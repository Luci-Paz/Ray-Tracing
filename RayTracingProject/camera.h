#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include <fstream>


class camera {
public:
	double aspectRatio = 1.0;	//Ratio of image width over height
	int imageWidth = 100;		//Rendered image width in pixel count
	int samplesPerPixel = 10;	//count of random samples for each pixel
	int maxDepth = 10;			//maximum number of ray bounces allowed 


	/// <summary>
	/// Renders the scene by writing each pixel to a .ppm file 
	/// </summary>
	/// <param name="world"></param>
	void render(const hittable& world) {
		
		initialize();
		
		//create an .ppm image 
		std::ofstream myfile("renderedImage.ppm");
		myfile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

		//Loops through each pixel to render them
		for (int i = 0; i < imageHeight; i++) {
			
			std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
			
			for (int j = 0; j < imageWidth; j++) {
				
				//find the color of each pixel and take random samples of surrounding pixels 
				//for antialiasing
				color pixelColor(0, 0, 0);
				for (int sample = 0; sample < samplesPerPixel; sample++) {
					ray r = getRay(j, i);
					pixelColor += rayColor(r, maxDepth, world);
				} //end inmost for

				writeColor(myfile, pixelSamplesScale * pixelColor);
			
			} //end inner for

		} //end outer for
		myfile.close();
		std::clog << "\rDone                  \n";

	} //end render()


private:
	int imageHeight;			//rendered image height
	double pixelSamplesScale;	//color scale factor for the sum of pixel samples
	point3 center;				//camera center
	point3 pixel00Loc;			//location of pixel 0,0
	vec3 pixelDeltaU;			//offset to pixel to the right
	vec3 pixelDeltaV;			//offset to pixel to below


	/// <summary>
	/// Initializes values for the scene and camera properties
	/// </summary>
	void initialize() {
		imageHeight = int(imageWidth / aspectRatio);
		imageHeight = (imageHeight < 1) ? 1 : imageHeight;

		pixelSamplesScale = 1.0 / samplesPerPixel;

		center = point3(0, 0, 0);

		//determine viewport dimensions
		auto focalLength = 1.0;
		auto viewportHeight = 2.0;
		auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

		//calculate the vectos across the horizontal and down the vertical edges
		auto viewportU = vec3(viewportWidth, 0, 0);
		auto viewportV = vec3(0, -viewportHeight, 0);

		//calculate the horizontal and vertical delta vectors from pixel to pixel
		pixelDeltaU = viewportU / imageWidth;
		pixelDeltaV = viewportV / imageHeight;

		//calculate the location of the upper left pixel
		auto viewportUpperLeft = center - vec3(0, 0, focalLength) - (viewportU / 2) - (viewportV / 2);
		pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

	} //end initialize()


	/// <summary>
	/// construct a camera ray from the origin that is directed to a randomly sampled point around 
	/// the pixel at location i,j
	/// </summary>
	/// <param name="i"></param> x-axis coordinate number
	/// <param name="j"></param> y-axis coordinate number
	/// <returns></returns> A ray pointed at a randomly sampled point around the pixel i,j
	ray getRay(int i, int j) const {
		// 

		auto offset = sampleSquare();
		auto pixelSample = pixel00Loc
			+ ((i + offset.x()) * pixelDeltaU)
			+ ((j + offset.y()) * pixelDeltaV);

		auto rayOrigin = center;
		auto rayDirection = pixelSample - rayOrigin;

		return ray(rayOrigin, rayDirection);

	}


	/// <summary>
	/// returns the vector to a random point in the [-0.5, -0.5] [+0.5, +0.5] unit square
	/// </summary>
	/// <returns></returns>
	vec3 sampleSquare() const {
		return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
	}


	//determines the color of the ray 
	color rayColor(const ray& r, int depth, const hittable& world) const {
		
		//if ray bounce limit is excceeded then no more light is gathered
		if (depth <= 0)
			return color(0, 0, 0);

		
		hitRecord rec;

		//if the ray hits an object, color it and simulate its reflection/bounce.
		//The interval min is 0.001 to remove shadow acne.
		if (world.hit(r, interval(0.001, infinity), rec)) { 
			vec3 direction = rec.normal + randomUnitVector();
			return 0.5 * rayColor(ray(rec.p, direction), depth-1, world); 
		} //end if

		
		vec3 unitDirection = unitVector(r.direction());
		auto a = 0.5 * (unitDirection.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + (a * color(0.5, 0.7, 1.0));

	} //end rayColor()


};



#endif // !CAMERA_H
