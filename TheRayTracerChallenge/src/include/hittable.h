#ifndef INCLUDE_HITTABLE_H
#define INCLUDE_HITTABLE_H

#include <cmath>

#include "Vec4.h"
#include "Matrix.h"
#include "Material.h"

#include "Ray.h"
#include "Intersection.h"

namespace RayTracer {

	namespace Utility {

		struct vertex_idx {
			int v, vn, vt;
		};

		struct shape_bounds {
			float x[2] = {INFINITY, -INFINITY};
			float y[2] = { INFINITY, -INFINITY };
			float z[2] = { INFINITY, -INFINITY };

			shape_bounds& operator =(const shape_bounds& other) {

				if (x[0] > other.x[0]) x[0] = other.x[0];
				if (y[0] > other.y[0]) y[0] = other.y[0];
				if (z[0] > other.z[0]) z[0] = other.z[0];
				if (x[1] < other.x[1]) x[1] = other.x[1];
				if (y[1] < other.y[1]) y[1] = other.y[1];
				if (z[1] < other.z[1]) z[1] = other.z[1];

				return *this;
			}
		};

		inline float max3f(const float& f1, const float& f2, const float& f3) {
			return f1 > f2 ? (f1 > f3 ? f1 : f3) : (f2 > f3 ? f2 : f3);
		}
		inline float min3f(const float& f1, const float& f2, const float& f3) {
			return f1 < f2 ? (f1 < f3 ? f1 : f3) : (f2 < f3 ? f2 : f3);
		}

		void split(std::string str, const std::string& token, std::vector<std::string>& result) {
			while (str.size()) {
				int index = str.find(token);
				if (index != std::string::npos) {
					result.push_back(str.substr(0, index));
					str = str.substr(index + token.size());
					if (str.size() == 0)
						result.push_back(str);
				}
				else {
					result.push_back(str);
					str = "";
				}
			}
		}

	}

	

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
			Utility::shape_bounds bounds;
			bounds.x[0] = -1;
			bounds.x[1] = 1;
			bounds.y[0] = -1;
			bounds.y[1] = 1;
			bounds.z[0] = -1;
			bounds.z[1] = 1;
			return bounds;
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