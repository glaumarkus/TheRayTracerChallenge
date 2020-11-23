#ifndef INCLUDE_CAMERA_H
#define INCLUDE_CAMERA_H

#include "Vec4.h"
#include "Ray.h"

namespace RayTracer {

	class Camera {
	public:

		Camera() :
			origin(Vec4(-20, 0, 0)), 
			forward(Vec4(1,0,0)),
			up(Vec4(0,0,1)),
			right(Vec4(0,-1,0))
		{
			h = tan(20.0f * PI / 180.f);
			w = h * 1;
		}

		Camera(
			const Vec4& lookfrom,
			const Vec4& lookat,
			const Vec4& upguide,
			const float& fov,
			const float& aspectRatio) :
			origin(lookfrom)
		{
			forward = (lookfrom - lookat).normalize();
			right = cross(upguide, forward).normalize();
			up = cross(forward, right).normalize();

			h = tan(fov);
			w = h * aspectRatio;
		};

		Ray getRay(const float& x, const float& y) const {
			return Ray(origin, (forward + x * w * right + y * h * up).normalize());
		};


	private:

		Vec4 origin;
		Vec4 forward, right, up;
		float h, w;

	};


}


#endif // !CAMERA_H