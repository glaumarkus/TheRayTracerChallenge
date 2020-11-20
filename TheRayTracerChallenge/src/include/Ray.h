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
		direction(r.direction)
	{};

    Ray(const Vec4& origin, const Vec4& direction) :
        origin(origin),
        direction(direction)
    {};


    void transform(const Mat4& m) {
        origin = m * origin;
        direction = m * direction;
    }

	Ray& transformed(const Mat4& m) {
		origin = m * origin;
		direction = m * direction;
        return *this;
	}

    Vec4 getOrigin() {
        return origin;
    }

    Vec4 getDirection() {
        return direction;
    }

    Vec4 position(float t) const {
        return Vec4(origin + direction * t);
    };

    Ray& operator =(const Ray& r) {
        origin = r.origin;
        direction = r.direction;
        return *this;
    };

    void print() {
        printf("Ray: (%f, %f, %f, %f) (%f, %f, %f, %f)\n", origin.x, origin.y, origin.z, origin.w, direction.x, direction.y, direction.z, direction.w);
    }

private:
	Vec4 origin;
	Vec4 direction;

};

}

#endif 