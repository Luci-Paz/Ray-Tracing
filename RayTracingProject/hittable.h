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
	bool frontFace;


	/*
	* Sets the direction of the normal to point against the ray by seeing 
	* if the ray is inside or outside of the object. If it is inside the 
	* object the normal is set to point inwards and if it is outside the object 
	* the normal is set to point outwards.
	*/
	void setFaceNormal(const ray& r, const vec3& outwardNormal) {
		
		//If the dot product of the ray and normal is less than 0 the normal
		//points outwards and if not the normal points inwards.
		frontFace = dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;

	} //end setFaceNormal()
};


class hittable {
public:
	virtual ~hittable() = default;

	virtual bool hit(const ray& r, double rayTMin, double rayTMax, hitRecord& rec) const = 0;
};

#endif //HITTABLE_H
