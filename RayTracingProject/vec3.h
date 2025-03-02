#ifndef VEC3_H
#define VEC3_H

//vec3 class stores gometric vectors and colors. Uses two aliases, point3 and color.


class vec3 {

public:

	//array to store vector values
	double e[3];


	//constructors
	vec3() : e{ 0, 0, 0 } {}									//default
	vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}	//user entered


	//setters for coordinates
	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }


	//operator overloads
	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	/*
	* add values from v to the values of e
	*/
	vec3& operator+=(const vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	} //end operator+=

	/*
	* Multiply all values of e by t
	*/
	vec3& operator*=(double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	} //end operator *=

	/*
	* mutltiply all values of e by 1/t
	*/
	vec3& operator/=(double t) {
		return *this *= 1 / t;
	} //end operator /=

	/*
	* gets the length of the vector
	*/
	double length() const {
		return std::sqrt(lengthSquared());
	} //end length()

	/*
	* gets the square of the vector length
	*/
	double lengthSquared() const {
		return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
	} //end lengthSquared()


	//creates a random arbitrary vector 
	static vec3 random() { return vec3(randomDouble(), randomDouble(), randomDouble()); }


	//create a random arbitrary vector with a min and max random variable of position
	static vec3 random(double min, double max) { 
		return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max)); 
	}

	
};


//point3 is an alias of vec3 to help with geometric clarity
using point3 = vec3;


//Vector utility functions

/*
* outputs the vector values
*/
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
} //end ostream operator<<


/*
* adds two vectors together
*/
inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
} //end opertor+


/*
* subtracts vector v from vector u
*/
inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
} //end operator-


/*
* multiplies two vectors together
*/
inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
} //end operator*


/*
* multiples a vector by a value t
*/
inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
} //end operator*


/*
* multiples the vector values by t
*/
inline vec3 operator*(const vec3& v, double t) {
	return t * v;
} //end operator*


/*
* divides the vector values by t
*/
inline vec3 operator/(const vec3 & v, double t) {
	return (1 / t) * v;
} //end operator/


/*
* return the dot product of two vectors
*/
inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
} //end dot()


/*
* return the cross/vector product of two vectors
*/
inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
} //end cross()


/*
* return the unit vector
*/
inline vec3 unitVector(const vec3& v) {
	return v / v.length();
} //end unitVector()


inline vec3 randomUnitVector() {
	
	//get a random vector that is within a unit sphere and 
	//normalize it to produce a unit vector
	while (true) {

		//create a new vector and find its length squared
		auto p = vec3::random(-1, 1);
		auto lensq = p.lengthSquared();

		//if the vector length squared is greater and 1e-160 and 
		//less than or equal to 1, normalize the vector p
		if (1e-160 < lensq && lensq <= 1)
			return p / sqrt(lensq);
	} //end while

} //end randomUnitVector()


inline vec3 randomOnHemisphere(const vec3& normal) {

	//get a random vector on the unit sphere
	vec3 onUnitSphere = randomUnitVector();

	//invert the direction of the unit vector if it is not
	//the same as the normal vector to the objects surface
	if (dot(onUnitSphere, normal) > 0.0)
		return onUnitSphere;
	else
		return -onUnitSphere;

}

#endif //VEC3_H
