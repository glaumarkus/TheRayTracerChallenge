#ifndef INCLUDE_OBJ_READER_H
#define INCLUDE_OBJ_READER_H

#include <string>
#include <string_view>

#include <sstream>
#include <fstream>

#include "Vertex_Handler.h"
#include "Triangle.h"

namespace RayTracer {

	class OBJ_Reader {
	public:

		OBJ_Reader(const std::string& filename, Material* material, Mat4&& transformation) :
			material(material),
			transformation(std::move(transformation))
		{
			vertices = new Vertex_Handler();
			normals = new Vertex_Handler();
			uv = new Vertex_Handler();

			read_file(filename);
		}

	private:

		void read_file(const std::string& filename) {
			std::ifstream file_(filename);
			if (!file_.is_open()) {
				printf("OBJ file not found!");
				return;
			}

			std::string line_;
			while (getline(file_, line_)) {


				if (line_[0] == '#') continue;
				if (line_.empty()) continue;

				if (line_[0] == 'f') {

					std::string tmp = line_.substr(2, line_.size() - 1);
					std::vector<std::string> vstrings;
					Utiliy::split(tmp, " ", vstrings);

					std::vector<int[3]> triangle_data;
					triangle_data.reserve(3);

					for (int i = 0; i < vstrings.size(); ++i) {
						if (vstrings[i].size() != 0) {
							std::vector<std::string> tmp2;
							Utiliy::split(vstrings[i], "/", tmp2);
							triangle_data.emplace_back(std::stoi(tmp2[0]), std::stoi(tmp2[2]), std::stoi(tmp2[1]));
						}
					}

					// build n Triangles
					for (int i = 1; i < triangle_data.size() - 1; ++i) {

						Vec4* p1 = vertices->vertices[triangle_data[0][0] - 1];
						Vec4* p2 = vertices->vertices[triangle_data[i][0] - 1];
						Vec4* p3 = vertices->vertices[triangle_data[i + 1][0] - 1];

						if (normals->vertices.size() != 0) {
							Vec4* n1 = normals->vertices[triangle_data[0][1] - 1];
							Vec4* n2 = normals->vertices[triangle_data[i][1] - 1];
							Vec4* n3 = normals->vertices[triangle_data[i + 1][1] - 1];
							Triangle* triangle = new Triangle(p1, p2, p3, n1, n2, n3, material);
							obj_triangles.push_back(triangle);
						}
						else {
							Triangle* triangle = new Triangle(p1, p2, p3, material);
							obj_triangles.push_back(triangle);
						}
							
					}
					continue;
				}

				std::stringstream input(line_);
				std::string paramName;
				input >> paramName;

				if (paramName == "v") {
					float x, y, z;
					input >> x >> y >> z;
					Vec4* vertex = new Vec4();
					*vertex = transformation * Vec4(x, y, z, 1);
					vertices->push_back(vertex);
				}
				else if (paramName == "vn") {
					float x, y, z;
					input >> x >> y >> z;
					Vec4* vertex = new Vec4();
					*vertex = transformation * Vec4(x, y, z, 1);
					normals->push_back(vertex);
				}
				else if (paramName == "vt") {
					float x, y;
					input >> x >> y;
					Vec4* vertex = new Vec4(x, y, 0.0f, 0.0f);
					uv->push_back(vertex);
				}

				// implement groups
				else if (paramName == "g") {	
				}

			}
		}

		Material* material;
		Mat4 transformation;

		Vertex_Handler* vertices;
		Vertex_Handler* normals;
		Vertex_Handler* uv;

		std::vector<hittable*> obj_triangles;
	};


	namespace Utiliy {
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
}




#endif // !INCLUDE_OBJ_READER_H