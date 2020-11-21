#ifndef INCLUDE_SPHERE_H
#define INCLUDE_SPHERE_H

#include <cmath>

#include "hittable.h"


namespace RayTracer {


	class Sphere : public transformed {
	public:

		Sphere(const Mat4& transformation, Material* material) :
			transformed(transformation, material)
		{}
		Sphere(Mat4&& transformation, Material* material) :
			transformed(std::move(transformation), material)
		{}


	protected:

		void local_intersection_test(Intersection& i, const Ray& ray) {

			float a, b, c;
			a = dot(ray.direction, ray.direction);
			b = 2 * dot(ray.direction, ray.origin);
			c = dot(ray.origin, ray.origin) - 1;

			float discriminant = b * b - 4.0f * a * c;

			if (discriminant < 0)
				return;

			float t1, t2;
			t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
			t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);

			Vec4 pt_on_sphere = ray.position(t1);
			float u = atan2f(pt_on_sphere.x, pt_on_sphere.z) / (2.0f * PI) + 0.5f;
			float v = pt_on_sphere.y * 0.5f + 0.5f;
			i.checkIntersection(t1, u, v, this);

			pt_on_sphere = ray.position(t2);
			u = atan2f(pt_on_sphere.x, pt_on_sphere.z) / (2.0f * PI) + 0.5f;
			v = pt_on_sphere.y * 0.5f + 0.5f;
			i.checkIntersection(t2, u, v, this);

		}

		Vec4 local_normal_at(const Vec4& transformed_point) {
			return transformed_point;
		}


	};



}




#endif