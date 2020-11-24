#ifndef INCLUDE_TORUS_H
#define INCLUDE_TORUS_H

#include <cmath>
#include "hittable.h"


namespace RayTracer {


	class Torus : public transformed {
	public:

		Torus(const Mat4& transformation, Material* material) :
			transformed(transformation, material)
		{}
		Torus(Mat4&& transformation, Material* material) :
			transformed(std::move(transformation), material)
		{}


	protected:

		void local_intersection_test(Intersection& i, const Ray& ray) {
		}


		Vec4 local_normal_at(const Vec4& transformed_point) {
			return transformed_point;
		}


	};



}




#endif