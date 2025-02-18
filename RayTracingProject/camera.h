#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include <fstream>


class camera {
public:
	double aspectRatio = 1.0;	//Ratio of image width over height
	int imageWidth = 100;		//Rendered image width in pixel count


	void render(const hittable& world) {
		initialize();
		
		std::ofstream myfile("renderedImage.ppm");
		myfile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

		for (int i = 0; i < imageHeight; i++) {
			std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
			for (int j = 0; j < imageWidth; j++) {
				auto pixelCenter = pixel00Loc + (j * pixelDeltaU) + (i * pixelDeltaV);
				auto rayDirection = pixelCenter - center;
				ray r(center, rayDirection);

				color pixelColor = rayColor(r, world);
				writeColor(myfile, pixelColor);
			
			} //end inner for

		} //end outer for
		myfile.close();
		std::clog << "\rDone                  \n";

	} //end render()


private:
	int imageHeight;
	point3 center;
	point3 pixel00Loc;
	vec3 pixelDeltaU;
	vec3 pixelDeltaV;


	void initialize() {
		imageHeight = int(imageWidth / aspectRatio);
		imageHeight = (imageHeight < 1) ? 1 : imageHeight;

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


	color rayColor(const ray& r, const hittable& world) const {
		hitRecord rec;

		if (world.hit(r, interval(0, infinity), rec)) { return 0.5 * (rec.normal + color(1, 1, 1)); }

		
		vec3 unitDirection = unitVector(r.direction());
		auto a = 0.5 * (unitDirection.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + (a * color(0.5, 0.7, 1.0));

	} //end rayColor()


};



#endif // !CAMERA_H
