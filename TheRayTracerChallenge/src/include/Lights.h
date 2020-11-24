#ifndef INCLUDE_LIGHT_H
#define INCLUDE_LIGHT_H

#include <vector>

#include "Vec4.h"
#include "Material.h"


namespace RayTracer {

	constexpr float PHI = PI * (3.0f - 2.236067f);

	class Light {
	public:

		Light(const Color& intensity, const Vec4& position) :
			intensity(intensity),
			position(position)
		{
			light_points.emplace_back(position);
		}

		Light(const Color& intensity, const Vec4& position, const int& i) :
			intensity(intensity),
			position(position)
		{}



		Color intensity;
		Vec4 position;
		std::vector<Vec4> light_points;

	};



	class SphereLight : public Light {
	public:

		SphereLight(const Color& intensity, const Vec4& position, const int& pts, const float& radius) : 
			Light(intensity, position, 0),
			pts(pts), 
			radius(radius)
		{

			light_points.reserve(pts);

			for (int i = 0; i < pts; i++) {
				
				float x, y, z;

				y = 1 - (i / (float)(pts - 1)) * 2;
				float theta = PHI * i;
				float rad = std::sqrt(1 - y * y);
				x = cos(theta) * rad * radius;
				z = sin(theta) * rad * radius;
				y *= radius;

				light_points.emplace_back(Vec4(x,y,z) + position);
			}
		}

		
	private:

		int pts;
		float radius;
		
	};

}



#endif