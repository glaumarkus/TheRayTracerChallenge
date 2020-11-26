#ifndef INCLUDE_GROUP_H
#define INCLUDE_GROUP_H

#include <cmath>
#include <list>

// replace list 

#include "hittable.h"
#include "Cube.h"
#include "Vertex_Handler.h"

namespace RayTracer {


	class Group : public hittable {
	public:

		/*
		* Constructor with or without transformation matrix
		*/
		Group(Material* material) :
			hittable(material),
			AABB(std::move(Matrix::Default_Matrix), &Materials::Black),
			transformation(std::move(Matrix::Default_Matrix))
		{
			transformation_inverse = std::move(transformation);
			transformation_inverse_transposed = std::move(transformation_inverse);
		}

		Group(Mat4&& transformation, Material* material) :
			hittable(material),
			AABB(transformation, &Materials::Black),
			transformation(std::move(transformation))
		{
			transformation_inverse = std::move(transformation);
			if (!inverse(transformation_inverse)) {
				std::cerr << "Error when inversing transformation matrix\n";
				throw(1);
			}
			transformation_inverse_transposed = std::move(transformation_inverse);
			transformation_inverse_transposed.transpose();
		}

		~Group() {
			for (auto& child : children) {
				delete child;
			}

			vertices->~Vertex_Handler();
			normals->~Vertex_Handler();
			uv->~Vertex_Handler();
		}

		int size() { return children.size(); }

		void add_child(hittable* child) {
			children.push_back(child);
		}

		void set_bounds() {
			
			for (auto& child : children) {
				bounding_box = child->getBounds();
			}

			float translate_x, translate_y, translate_z, scale_x, scale_y, scale_z;

			scale_x = (bounding_box.x[1] - bounding_box.x[0]) / 2;
			scale_y = (bounding_box.y[1] - bounding_box.y[0]) / 2;
			scale_z = (bounding_box.z[1] - bounding_box.z[0]) / 2;

			translate_x = bounding_box.x[1] - scale_x;
			translate_y = bounding_box.y[1] - scale_y;
			translate_z = bounding_box.z[1] - scale_z;

			scale_x = scale_x > 0.1f ? scale_x : 0.1f;
			scale_y = scale_y > 0.1f ? scale_y : 0.1f;
			scale_z = scale_z > 0.1f ? scale_z : 0.1f;

			Mat4 child_transform = translate(translate_x, translate_y, translate_z) * scale(scale_x, scale_y, scale_z);
			AABB.transformation = transformation * child_transform;
			AABB.transformation_inverse = std::move(AABB.transformation);
			if (!inverse(AABB.transformation_inverse)) throw(1);
			AABB.transformation_inverse_transposed = std::move(AABB.transformation_inverse);
			AABB.transformation_inverse_transposed.transpose();

		}

		void intersection_test(Intersection& i, const Ray& ray) {

			Intersection BB_intersection;
			AABB.intersection_test(BB_intersection, ray);

			if (BB_intersection.observation.t == INFINITY) return;
			

			for (auto& child : children) {
				Ray transformed_ray(ray.transformed(transformation_inverse));
				child->intersection_test(i, transformed_ray);
			}
		}

		float shadow_intersection() { return 1.0f; };
		Vec4 normal_at(const Vec4& point, const float& u, const float& v) { return Vec4(); };
		Vec4 getLocalPoint(const Vec4& point) { return Vec4(); };

		Mat4& get_transformation() { return transformation;	}

		Utility::shape_bounds getBounds() { return bounding_box; };


	protected:

		friend class OBJ_Reader;

		Cube AABB;
		Utility::shape_bounds bounding_box;
		Mat4 transformation;
		Mat4 transformation_inverse;
		Mat4 transformation_inverse_transposed;

		std::list<hittable*> children;

		Vertex_Handler* vertices;
		Vertex_Handler* normals;
		Vertex_Handler* uv;

	};


}


#endif