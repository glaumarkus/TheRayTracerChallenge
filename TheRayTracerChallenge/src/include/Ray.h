#ifndef INCLUDE_RAY_H
#define INCLUDE_RAY_H

#include "Vec4.h"
#include "Matrix.h"

namespace RayTracer {

    class Ray {
    public:

	    Ray() {}

	    Ray(const Ray& r) :
		    origin(r.origin),
		    direction(r.direction),
            n1(1.0f)
	    {};

        Ray(Ray&& r) :
            origin(std::move(r.origin)),
            direction(std::move(r.direction)),
            n1(r.n1)
        {};

        Ray(const Vec4& origin, const Vec4& direction) :
            origin(origin),
            direction(direction),
            n1(1.0f)
        {};

        Ray(const Vec4& origin, const Vec4& direction, const float& n1) :
            origin(origin),
            direction(direction),
            n1(n1)
        {};


        void transform(const Mat4& m) {
            origin = m * origin;
            direction = m * direction;
        }

	    Ray transformed(const Mat4& m) const {
            return Ray(m * origin, m * direction);
            //return Ray(Vec4(m * origin), Vec4(m * direction));
	    }

        Vec4 position(float t) const {
            return Vec4(origin + direction * t);
        };

        Ray& operator =(const Ray& r) {
            origin = r.origin;
            direction = r.direction;
            n1 = r.n1;
            return *this;
        };

        void print() {
            printf("Ray: (%f, %f, %f, %f) (%f, %f, %f, %f)\n", origin.x, origin.y, origin.z, origin.w, direction.x, direction.y, direction.z, direction.w);
        }

	    Vec4 origin;
	    Vec4 direction;
        float n1;

    };

}

#endif 