#ifndef INCLUDE_OBJ_READER_H
#define INCLUDE_OBJ_READER_H

#include <string>
#include <string_view>

#include <sstream>
#include <fstream>

#include "Vertex_Handler.h"
#include "Triangle.h"
#include "Group.h"

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

		void copy_data(Group& obj) {
			
			// move pointers
			obj.vertices = vertices;
			vertices = nullptr;
			obj.normals = normals;
			normals = nullptr;
			obj.uv = uv;
			uv = nullptr;

			for (auto& g : triangle_groups)
				obj.add_child(g);
			obj.set_bounds();
		}

	private:

		friend class Group;

		void read_file(const std::string& filename) {
			std::ifstream file_(filename);
			if (!file_.is_open()) {
				printf("OBJ file not found!");
				return;
			}

			Group* firstGroup = new Group(std::move(transformation), material);

			std::string line_;
			while (getline(file_, line_)) {


				if (line_[0] == '#') continue;
				if (line_.empty()) continue;

				if (line_[0] == 'f') {

					std::string tmp = line_.substr(2, line_.size() - 1);
					std::vector<std::string> vstrings;
					Utility::split(tmp, " ", vstrings);

					std::vector<Utility::vertex_idx> triangle_data;
					triangle_data.reserve(3);

					for (auto i = 0; i < vstrings.size(); ++i) {
						if (vstrings[i].size() != 0) {

							std::vector<std::string> tmp2;
							Utility::split(vstrings[i], "/", tmp2);

							Utility::vertex_idx tmp_idx;
							tmp_idx.v = std::stoi(tmp2[0]);
							tmp_idx.vn = std::stoi(tmp2[2]);
							if (tmp2[1] != "") tmp_idx.vt = std::stoi(tmp2[1]);
							else tmp_idx.vt = -1;

							triangle_data.push_back(tmp_idx);
						}
					}

					// build n Triangles
					for (auto i = 1; i < triangle_data.size() - 1; ++i) {

						Vec4* p1 = vertices->vertices[triangle_data[0].v - 1];
						Vec4* p2 = vertices->vertices[triangle_data[i].v - 1];
						Vec4* p3 = vertices->vertices[triangle_data[i + 1].v - 1];

						if (normals->vertices.size() != 0) {
							Vec4* n1 = normals->vertices[triangle_data[0].vn - 1];
							Vec4* n2 = normals->vertices[triangle_data[i].vn - 1];
							Vec4* n3 = normals->vertices[triangle_data[i + 1].vn - 1];
							Triangle* triangle = new Triangle(p1, p2, p3, n1, n2, n3, material);
							firstGroup->add_child(triangle);
						}
						else {
							Triangle* triangle = new Triangle(p1, p2, p3, material);
							firstGroup->add_child(triangle);
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

					if (firstGroup->size() != 0) {
						firstGroup->set_bounds();
						triangle_groups.push_back(firstGroup);
						firstGroup = new Group(std::move(transformation), material);
					}
					
				}

			}

			firstGroup->set_bounds();
			triangle_groups.push_back(firstGroup);
		}

		Material* material;
		Mat4 transformation;

		Vertex_Handler* vertices;
		Vertex_Handler* normals;
		Vertex_Handler* uv;

		std::vector<hittable*> triangle_groups;
	};


}




#endif // !INCLUDE_OBJ_READER_H