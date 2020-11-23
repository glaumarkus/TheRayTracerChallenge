#ifndef INCLUDE_LIGHT_H
#define INCLUDE_LIGHT_H

#include <vector>

#include "Vec4.h"
#include "Material.h"


namespace RayTracer {

	class Light {
	public:

		Light(const Color& intensity, const Vec4& position) :
			intensity(intensity),
			position(position)
		{
			light_points.emplace_back(position);
		}



		Color intensity;
		Vec4 position;
		std::vector<Vec4> light_points;
	};



	class SphereLight : public Light {
	public:

		SphereLight(const Color& intensity, const Vec4& position, const int& pts = 10, const float& radius = 5.0f) : 
			Light(intensity, position), 
			pts(pts), 
			radius(radius) 
		{
			light_points.reserve(pts);

			for (int i = 0; i < pts; i++) {
				float phi = PI * (3.0f - std::sqrt(5.0f));
				float x, y, z;
				float h = (float)i / (pts - 1);
				h *= radius;
				y = 1.0f - h;

				float tmp = 1 - y * y;
				float radius = std::sqrt(tmp);
				float t = phi * i;

				x = cos(t) * radius;
				z = sin(t) * radius;

				light_points.emplace_back(x, y, z);
			}
		}

		
	private:

		int pts;
		float radius;
		
	};

}



#endif