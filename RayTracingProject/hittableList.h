#ifndef HITTABLELIST_H
#define HITTABLELIST_H


/*
* Header file outlines hittableList class that allows for the creation
* of a vector of hittable objects.
*/


#include "hittable.h"
#include <vector>


class hittableList : public hittable {
public:
	//create a vector of hittable object shared pointers
	std::vector<shared_ptr<hittable>> objects;


	hittableList() {}
	hittableList(shared_ptr<hittable> object) { add(object); }

	void clear() { objects.clear(); } //end clear()

	void add(shared_ptr<hittable> object) { objects.push_back(object); } //end add()

	bool hit(const ray& r, interval rayT, hitRecord& rec) const override {
		hitRecord tempRec;
		bool hitAnything = false;
		auto closestSoFar = rayT.max;

		for (const auto& object : objects) {
			if (object->hit(r, interval(rayT.min, closestSoFar), tempRec)) {
				hitAnything = true;
				closestSoFar = tempRec.t;
				rec = tempRec;
			} //end if
		} //end loop

		return hitAnything;

	} //end hit()
};

#endif // !HITTABLELIST_H


