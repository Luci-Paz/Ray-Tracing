#ifndef COLOR_H
#define COLOR_H

//header file for the ray alias color that describes a function to convert vector data
//into a pixel color


#include "vec3.h"

using color = vec3;


void writeColor(std::ostream& out, const color& pixelColor) {
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	//translate the [0,1] values to the byte range [0,255]
	int rbyte = int(255.999 * r);
	int gbyte = int(255.999 * g);
	int bbyte = int(255.999 * b);

	//write out the pixel color components
	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}


#endif //COLOR_H
