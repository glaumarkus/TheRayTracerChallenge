#ifndef RAY_HPP
#define RAY_HPP

#include "Vec4.h"
#include "Matrix.h"

class Ray {
private:
    Vec4 origin;
    Vec4 direction;
public:
    Ray() {
        origin = Vec4(0, 0, 0, 1);
        direction = Vec4(1, 0, 0, 0);
    }

    Ray(const Ray& r) :
        origin(r.origin),
        direction(r.direction)
    {};

    Ray(const Vec4& origin, const Vec4& direction) :
        origin(origin),
        direction(direction)
    {};

    void transform(Mat4& m) {
        origin = m * origin;
        direction = m * direction;
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
};

#endif 