#ifndef INCLUDE_HITTABLE_H
#define INCLUDE_HITTABLE_H

#include <cmath>

#include "Vec4.h"
#include "Matrix.h"
#include "Material.h"

#include "Ray.h"
#include "Intersection.h"

namespace RayTracer {

	class hittable {

	public:

		hittable(){}
		~hittable(){}

		virtual void intersection_test(Intersection& i, const Ray& ray) = 0;
		virtual float shadow_intersection() = 0;
		virtual Vec4 normal_at(const Vec4& point) = 0;

	};


	class transformed : public hittable {
	public:

		/*
		* Constructor
		*/
		transformed(const Mat4& transformation, Material* material) :
			transformation(transformation),
			material(material)
		{
			transformation_inverse = transformation;
			if (!inverse(transformation_inverse)) {
				std::cerr << "Error when inversing transformation matrix\n";
				throw(1);
			}
		}

		/*
		* Copy Constructor
		*/

		transformed(Mat4&& transformation, Material* material) :
			transformation(std::move(transformation)),
			material(material)
		{
			transformation_inverse = std::move(transformation);
			if (!inverse(transformation_inverse)) {
				std::cerr << "Error when inversing transformation matrix\n";
				throw(1);
			}
			transformation_inverse_transposed = std::move(transformation_inverse);
			transformation_inverse_transposed.transpose();
		}

		/*
		* Destructor
		*/
		~transformed() {}

		/*
		* transforms ray into local coordinate system and calls virtual intersect function
		*/
		void intersection_test(Intersection& i, const Ray& ray) {
			Ray transformed_ray = ray.transformed(transformation_inverse);
			local_intersection_test(i, transformed_ray);
		}
		virtual void local_intersection_test(Intersection& i, const Ray& ray) = 0;


		/*
		* transforms point into local coordinate system and calls virtual normal function
		*/
		Vec4 normal_at(const Vec4& point) {

			Vec4 transformed_normal = local_normal_at(
				transformation_inverse * point
			);

			Vec4 world_normal = transformation_inverse_transposed * transformed_normal;

			world_normal.w = 0.0f;
			world_normal.norm();

			return world_normal;
		};

		virtual Vec4 local_normal_at(const Vec4& transformed_point) = 0;

		float shadow_intersection() { return 1.0f; }


	protected:
		Mat4 transformation;
		Mat4 transformation_inverse;
		Mat4 transformation_inverse_transposed;
		Material* material;
	};


}



#endif