#ifndef COMMONITEMS_H
#define COMMONITEMS_H


/*
* Contains commonly used constants and functions
*/


#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>



//C++ std usings
using std::make_shared;
using std::shared_ptr;


//constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


//utility functions ============================================================
inline double degreesToRadians(double degrees) { return degrees * pi / 180; }

//returns a random real between [0,1)
inline double randomDouble() { return std::rand() / (RAND_MAX + 1.0); }

//returns a random real between [min,max)
inline double randomDouble(double min, double max) { return min + (max - min) * randomDouble(); }


//common headers ================================================================
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "interval.h"

#endif // !COMMONITEMS_H


