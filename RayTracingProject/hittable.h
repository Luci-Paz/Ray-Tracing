#ifndef HITTABLE_H
#define HITTABLE_H

//Header file for an abstract class that gives basic functions that a 
//hittable object should have


#include "ray.h"


class hitRecord {
public:
	point3 p;
	vec3 normal;
	double t;
};


class hittable {
public:
	virtual ~hittable() = default;

	virtual bool hit(const ray& r, double rayTMin, double rayTMax, hitRecord& rec) const = 0;
};

#endif //HITTABLE_H
