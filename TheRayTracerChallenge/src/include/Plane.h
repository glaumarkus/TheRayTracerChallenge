#ifndef INCLUDE_PLANE_H
#define INCLUDE_PLANE_H

#include <cmath>
#include "hittable.h"


namespace RayTracer {


	class Plane : public transformed {
	public:

		Plane(const Mat4& transformation, Material* material) :
			transformed(transformation, material)
		{}
		Plane(Mat4&& transformation, Material* material) :
			transformed(std::move(transformation), material)
		{}


	protected:

		void local_intersection_test(Intersection& i, const Ray& ray) {

			if (std::abs(ray.direction.z) < EPSILON) return;
			float t = -ray.origin.z / ray.direction.z;
			i.checkIntersection(t, this);
		}

		Vec4 local_normal_at(const Vec4& transformed_point) {
			return Vec4(0,0,1,0);
		}


	};

}


#endif