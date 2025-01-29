#ifndef RAY_H
#define RAY_H

//Header file that defines a function to determine what color is seen
//along a ray


#include "vec3.h"


class ray {
private:
	point3 orig;
	vec3 dir;


public:
	
	//constructors
	ray() {}

	ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}


	//member functions
	/*
	* return reference to point origin
	*/
	const point3& origin() const { return orig; }
	//end origin()


	/*
	* return reference to vector direction
	*/
	const vec3& direction() const { return dir; }
	//end direction()


	/*
	* return the position 
	*/
	point3 at(double t) { return orig + (t * dir); }
	//end at()

};




#endif //RAY_H