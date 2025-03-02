#ifndef COLOR_H
#define COLOR_H

//header file for the ray alias color that describes a function to convert vector data
//into a pixel color


#include "vec3.h"
#include "interval.h"
#include <fstream>

using color = vec3;


inline double linearToGamma(double linearComponent) {
	if (linearComponent > 0)
		//return std::sqrt(linearComponent);
		return std::pow(linearComponent, (1/2.2));
	
	return 0;
}


/// <summary>
/// take pixel data and write the color to the ofstream 'out'
/// </summary>
/// <param name="out"></param>
/// <param name="pixelColor"></param>
void writeColor(std::ofstream& out, const color& pixelColor) {
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();


	//Apply linear to gamma transformation for gamma 2.2
	r = linearToGamma(r);
	g = linearToGamma(g);
	b - linearToGamma(b);

	//translate the [0,1] values to the byte range [0,255]
	static const interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	//write out the pixel color components
	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
} //end writeColor()


#endif //COLOR_H
