#ifndef INCLUDE_UTILITY_H
#define INCLUDE_UTILITY_H

#include <string>
#include <vector>

#include "Vec4.h"


namespace RayTracer {

	namespace Utility {



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

		struct vertex_idx {
			int v, vn, vt;
		};

		struct shape_bounds {
			float x[2] = { INFINITY, -INFINITY };
			float y[2] = { INFINITY, -INFINITY };
			float z[2] = { INFINITY, -INFINITY };

			shape_bounds() {}
			shape_bounds(const Vec4& v_min, const Vec4& v_max) {
				x[0] = v_min.x;
				y[0] = v_min.y;
				z[0] = v_min.z;
				x[1] = v_max.x;
				y[1] = v_max.y;
				z[1] = v_max.z;
			}
			shape_bounds(const Vec4& v1, const Vec4& v2, const Vec4& v3) {
				x[0] = min3f(v1.x, v2.x, v3.x);
				y[0] = min3f(v1.y, v2.y, v3.y);
				z[0] = min3f(v1.z, v2.z, v3.z);
				x[1] = max3f(v1.x, v2.x, v3.x);
				y[1] = max3f(v1.y, v2.y, v3.y);
				z[1] = max3f(v1.z, v2.z, v3.z);
			}

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

		const Vec4 default_min_bounds(-1, -1, -1, 1);
		const Vec4 default_max_bounds(1, 1, 1, 1);
		const shape_bounds default_bounds(default_min_bounds, default_max_bounds);


	}

}

#endif