#ifndef SPHERE_H
#define SPHERE_H

//Header file for a hittable sphere object


#include "hittable.h"
#include "vec3.h"


class sphere : public hittable {
private:
	point3 center;
	double radius;


public:
	sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

	bool hit(const ray& r, double rayTMin, double rayTMax, hitRecord& rec) const override {
		
		//find how many times a ray intersects the sphere
		vec3 oc = center - r.origin();
		auto a = r.direction().lengthSquared();
		auto h = dot(r.direction(), oc);
		auto c = oc.lengthSquared() - radius * radius;

		auto discriminant = (h * h) - (a * c);
		
		//the event the ray does not hit the sphere
		if (discriminant < 0)
			return false;

		auto sqrtd = std::sqrt(discriminant);


		//find the nearest root within the acceptable range


	}


};




#endif // !SPHERE_H

