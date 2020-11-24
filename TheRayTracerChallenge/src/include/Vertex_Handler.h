#ifndef INCLUDE_VERTEX_HANDLER_H
#define INCLUDE_VERTEX_HANDLER_H

#include <vector>
#include "Vec4.h"

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

		std::vector<Vec4*> vertices;
	};

}

#endif // !INCLUDE_VERTEX_HANDLER_H