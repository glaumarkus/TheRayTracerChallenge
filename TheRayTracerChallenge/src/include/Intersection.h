#ifndef INCLUDE_INTERSECTION_HPP
#define INCLUDE_INTERSECTION_HPP

#include "Vec4.h"
#include "Ray.h"
#include "Observation.h"

namespace RayTracer {


    class Intersection {
    public:

        Intersection()
        {}

        ~Intersection()
        {}

        // overloading with u/v
        void checkIntersection(const float& t, hittable* hit) {
            if (t > 0.0f) {
                if (t < observation.t) {
                    observation = Observation(t, hit);
                }
            }
        }

        void checkIntersection(const float& t, const float& u, const float& v, hittable* hit) {
            if (t > 0.0f) {
                if (t < observation.t) {
                    observation = Observation(t, u, v, hit);
                }
            }
        }

        Observation observation;

    };

}

#endif