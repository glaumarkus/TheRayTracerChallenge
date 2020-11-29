#ifndef INCLUDE_TRIANGLE_H
#define INCLUDE_TRIANGLE_H

#include <cmath>
#include "hittable.h"


namespace RayTracer {

	class Triangle : public hittable {
	public:

		
		Triangle(const Vec4* v1, const Vec4* v2, const Vec4* v3, Material* material) :
			hittable(material),
			vertex1(v1), vertex2(v2), vertex3(v3),
			e1(*v2 - *v1),
			e2(*v3 - *v1),
			has_normal(0),
			normal(cross(e2, e1).normalize()),
			normal_v1(nullptr),
			normal_v2(nullptr),
			normal_v3(nullptr)
		{}
		



		Triangle(
			const Vec4* v1, const Vec4* v2, const Vec4* v3,
			const Vec4* n1, const Vec4* n2, const Vec4* n3,
			Material* material) :

			hittable(material),
			vertex1(v1), vertex2(v2), vertex3(v3),
			normal_v1(n1), normal_v2(n2), normal_v3(n3),
			e1(*v2 - *v1),
			e2(*v3 - *v1),
			has_normal(1),
			normal(1)
		{}

		void intersection_test(Intersection& i, const Ray& ray) {

			Vec4 dir_cross_e2 = cross(ray.direction, e2);
			float det = dot(e1, dir_cross_e2);

			if (std::abs(det) < EPSILON) return;
			
			float f = 1.0f / det;
			Vec4 p1_to_origin = ray.origin - *vertex1;
			float u = f * dot(p1_to_origin, dir_cross_e2);

			if (u < 0 || u > 1) return;

			Vec4 origin_cross_e1 = cross(p1_to_origin, e1);
			float v = f * dot(ray.direction, origin_cross_e1);

			if (v < 0 || (u + v) > 1) return;

			float t = f * dot(e2, origin_cross_e1);
			i.checkIntersection(t, u, v, this);
		}

		Vec4 normal_at(const Vec4& point, const float& u, const float& v) {

			if (has_normal == 0) {
				return normal;
			}
			return Vec4(*normal_v2 * u + *normal_v3 * v + *normal_v1 * (1 - u - v));
		}

		Vec4 getLocalPoint(const Vec4& point) {
			return point;
		}

		Utility::shape_bounds getBounds() {
			return Utility::shape_bounds(*vertex1, *vertex2, *vertex3);
		}

		float shadow_intersection() { return 0.0f; }

	protected:


		
		// Positions
		const Vec4* vertex1;
		const Vec4* vertex2;
		const Vec4* vertex3;

		const Vec4 e1;
		const Vec4 e2;

		const Vec4 normal;

		const uint_fast8_t has_normal;
		const Vec4* normal_v1;
		const Vec4* normal_v2;
		const Vec4* normal_v3;

		/*
		const Vec4 uv_v1;
		const Vec4 uv_v2;
		const Vec4 uv_v3;
		*/

	};

}




#endif

