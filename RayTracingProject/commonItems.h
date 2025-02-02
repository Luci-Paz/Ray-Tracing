#ifndef COMMONITEMS_H
#define COMMONITEMS_H


/*
* Contains commonly used constants and functions
*/


#include <cmath>
#include <iostream>
#include <limits>
#include <memory>


//C++ std usings
using std::make_shared;
using std::shared_ptr;


//constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


//utility functions
inline double degreesToRadians(double degrees) { return degrees * pi / 180; }


#endif // !COMMONITEMS_H


