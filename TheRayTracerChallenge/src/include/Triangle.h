#ifndef INCLUDE_TRIANGLE_H
#define INCLUDE_TRIANGLE_H

#include <cmath>
#include <vector>
#include "hittable.h"


namespace RayTracer {

	class Vertex_Handler {
	public:
		Vertex_Handler() {}

		~Vertex_Handler() {
			for (auto vertex : vertices) {
				delete vertex;
			}
		}

		void push_back(Vec4* vertex) {
			vertices.push_back(vertex);
		}

	private:
		std::vector<Vec4*> vertices;
	};


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
			normal()
		{}

		void intersection_test(Intersection& i, const Ray& ray) {
		}

		Vec4 normal_at(const Vec4& transformed_point) {
			return Vec4(0, 0, 1, 0);
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

