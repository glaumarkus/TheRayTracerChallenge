#ifndef INCLUDE_HITTABLE_H
#define INCLUDE_HITTABLE_H

#include <cmath>

#include "Utility.h"
#include "Vec4.h"
#include "Matrix.h"
#include "Material.h"

#include "Ray.h"
#include "Intersection.h"

namespace RayTracer {



	class hittable {

	public:

		hittable(Material* material) : material(material) {}
		~hittable(){}

		virtual void intersection_test(Intersection& i, const Ray& ray) = 0;
		virtual float shadow_intersection() = 0;
		virtual Vec4 normal_at(const Vec4& point, const float& u, const float& v) = 0;
		virtual Vec4 getLocalPoint(const Vec4& point) = 0;
		
		virtual Utility::shape_bounds getBounds() = 0;

		Material* getMaterial() { return material; }

	protected:
		Material* material;

	};


	class transformed : public hittable {
	public:

		/*
		* Constructor
		*/
		transformed(const Mat4& transformation, Material* material) :
			transformation(transformation),
			hittable(material)
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
			hittable(material)
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
		Vec4 normal_at(const Vec4& point, const float& u, const float& v) {

			Vec4 transformed_normal = local_normal_at(
				transformation_inverse * point
			);

			Vec4 world_normal = transformation_inverse_transposed * transformed_normal;

			world_normal.w = 0.0f;
			world_normal.norm();

			return world_normal;
		};
		virtual Vec4 local_normal_at(const Vec4& transformed_point) = 0;

		Vec4 getLocalPoint(const Vec4& point) {
			return Vec4(transformation_inverse * point);
		}

		
		Utility::shape_bounds getBounds() {

			/*
			* edit values 
			*/
			const Vec4 transformed_min(transformation * Utility::default_min_bounds);
			const Vec4 transformed_max(transformation * Utility::default_max_bounds);
			return Utility::shape_bounds(transformed_min, transformed_max);;
		}
		
		float shadow_intersection() { return 1.0f; }


	protected:
		Mat4 transformation;
		Mat4 transformation_inverse;
		Mat4 transformation_inverse_transposed;

		friend class Group;
		
	};


}



#endif