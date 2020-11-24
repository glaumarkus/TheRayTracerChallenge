#ifndef INCLUDE_CUBE_H
#define INCLUDE_CUBE_H

#include <cmath>
#include "hittable.h"


namespace RayTracer {


	class Cube : public transformed {
	public:

		Cube(const Mat4& transformation, Material* material) :
			transformed(transformation, material)
		{}
		Cube(Mat4&& transformation, Material* material) :
			transformed(std::move(transformation), material)
		{}


	protected:

		void local_intersection_test(Intersection& i, const Ray& ray) {

			t_helper xt = check_axis(ray.origin.x, ray.direction.x);
			t_helper yt = check_axis(ray.origin.y, ray.direction.y);
			t_helper zt = check_axis(ray.origin.z, ray.direction.z);
			
			float t1 = max3f(xt.t1, yt.t1, zt.t1);
			float t2 = min3f(xt.t2, yt.t2, zt.t2);

			if (t1 > t2) return;
			// optional u,v
			i.checkIntersection(t1, this);
			i.checkIntersection(t2, this);
		}


		Vec4 local_normal_at(const Vec4& transformed_point) {

			Vec4 normal(0, 0, 0, 0);
			float ax, ay, az;
			ax = std::abs(transformed_point.x);
			ay = std::abs(transformed_point.y);
			az = std::abs(transformed_point.z);
			float maxv = max3f(ax, ay, az);

			if (maxv == ax)
				normal.x = transformed_point.x;
			else if (maxv == ay)
				normal.y = transformed_point.y;
			else 
				normal.z = transformed_point.z;

			return normal;
		}

		
		/*
		* Helper functions
		*/
		struct t_helper {
			float t1, t2;
		};

		t_helper check_axis(const float& origin, const float& direction) {

			t_helper t;

			float tmin_num = (-1 - origin);
			float tmax_num = (1 - origin);

			if (std::abs(direction) >= EPSILON) {
				t.t1 = tmin_num / direction;
				t.t2 = tmax_num / direction;
			}
			else {
				t.t1 = tmin_num * INFINITY;
				t.t2 = tmax_num * INFINITY;
			}

			if (t.t1 > t.t2) {
				float tmp = t.t1;
				t.t1 = t.t2;
				t.t2 = tmp;
			}

			return t;
		}


		float max3f(const float& f1, const float& f2, const float& f3) {
			return f1 > f2 ? (f1 > f3 ? f1 : f3) : (f2 > f3 ? f2 : f3);
		}
		float min3f(const float& f1, const float& f2, const float& f3) {
			return f1 < f2 ? (f1 < f3 ? f1 : f3) : (f2 < f3 ? f2 : f3);
		}

	};


}


#endif