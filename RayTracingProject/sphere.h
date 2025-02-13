#ifndef SPHERE_H
#define SPHERE_H

//Header file for a hittable sphere object


#include "hittable.h"


class sphere : public hittable {
private:
	point3 center;
	double radius;


public:
	//constructor
	sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}


	//returns whether or not a ray hits the sphere
	bool hit(const ray& r, interval rayT, hitRecord& rec) const override {
		
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
		auto root = (h - sqrtd) / a;
		if (!rayT.surrounds(root)) {
			root = (h + sqrtd) / a;
			if (!rayT.surrounds(root))
				return false;
		} //end if


		//determine the surface side	
		rec.t = root;
		rec.p = r.at(rec.t);
		vec3 outwardNormal = (rec.p - center) / radius;
		rec.setFaceNormal(r, outwardNormal);

		return true;

	} //end hit()


};




#endif // !SPHERE_H

