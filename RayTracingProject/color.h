#ifndef COLOR_H
#define COLOR_H

//header file for the ray alias color that describes a function to convert vector data
//into a pixel color


#include "vec3.h"
#include "interval.h"
#include <fstream>

using color = vec3;


void writeColor(std::ofstream& out, const color& pixelColor) {
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	//translate the [0,1] values to the byte range [0,255]
	static const interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	//write out the pixel color components
	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}


#endif //COLOR_H
