#ifndef INTERVAL_H
#define INTERVAL_H

/**
* Manages real-valued intervals with a minimum and maximum value.
*/

#include "commonItems.h"

class interval {
public:
	double min, max;

	interval() : min(+infinity), max(-infinity) {} //default constructor

	interval(double min, double max) : min(min), max(max) {}

	//return the length of the interval
	double size() const { return max - min; }

	//return whether the interval contains a value x
	bool contains(double x) const { return min <= x && x <= max; }

	//return whether the value x is surrounded by the interval
	bool surrounds(double x) const { return min < x && x < max; }

	//declare empty and universal interavls
	static const interval empty, universe;

};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
	

#endif // !INTERVAL_H

