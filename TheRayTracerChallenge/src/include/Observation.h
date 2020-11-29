#ifndef INCLUDE_OBSERVATION_H
#define INCLUDE_OBSERVATION_H

#include "Vec4.h"

namespace RayTracer {

	// placeholder for objects
	class hittable;


	struct Observation {

		Observation() :
			t(INFINITY),
			u(INFINITY),
			v(INFINITY),
			hit(nullptr)
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
			hit(other.hit)
		{}

		Observation& operator =(const Observation& other) {
			t = other.t;
			u = other.u;
			v = other.v;
			hit = other.hit;
			return *this;
		}

		bool operator >(const Observation& other) const {
			return t > other.t ? true : false;
		}

		
		bool operator <(const Observation& other) const {
			return t < other.t ? true : false;
		}

		bool operator ==(const Observation& other)  {
			return std::fabs(t - other.t) < EPSILON ? true : false;
		}

		bool operator !=(const Observation& other)  {
			return std::fabs(t - other.t) > EPSILON ? true : false;
		}

		float t;
		float u;
		float v;
		hittable* hit;
	};

}

#endif 