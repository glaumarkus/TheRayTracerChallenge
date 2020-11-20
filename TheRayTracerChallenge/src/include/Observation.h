#ifndef INCLUDE_OBSERVATION_H
#define INCLUDE_OBSERVATION_H

#include "Vec4.h"

// placeholder for objects
class hittable;

struct Observation {
public:

	Observation()
	{}

	Observation(const float& t, hittable* hit) :
		t(t),
		u(INFINITY),
		v(INFINITY),
		hit(hit)
	{}

	Observation(const float& t, const float& u, const float& v, hittable* hit) :
		t(t),
		u(u),
		v(v),
		hit(hit)
	{}

	Observation(const Observation& other) :
		t(other.t),
		u(other.u),
		v(other.v),
		hit(hit)
	{}

	Observation& operator =(const Observation& other) {
		t = other.t;
		u = other.u;
		v = other.v;
		hit = other.hit;
		return *this;
	}

	Observation& operator =(Observation&& other) {
		t = other.t;
		u = other.u;
		v = other.v;
		hit = other.hit;
		return *this;
	}

	float t, u, v;
	hittable* hit;
};


#endif // 
