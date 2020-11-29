#ifndef INCLUDE_PATTERN_H
#define INCLUDE_PATTERN_H

#include "Vec4.h"

namespace RayTracer {


	class Pattern {
	public:
		Pattern(){}

		virtual Color color_at(const Vec4& point) { return Color(0); }

	};

	class Striped : public Pattern {
	public:
		Striped(const Color& color1, const Color& color2) : 
			color1(color1), 
			color2(color2),
			Pattern() 
		{}

		Color color_at(const Vec4& point) {
			float r = std::fabsf((float)fmod(std::floor(point.z), 2));
			return (r >= 1) ? color1 : color2;
		}

	private:
		Color color1;
		Color color2;
	};

	class Ring : public Pattern {
	public:
		Ring(const Color& color1, const Color& color2) :
			color1(color1),
			color2(color2),
			Pattern()
		{}

		Color color_at(const Vec4& point) {
			float r = (float)fmod(std::fabsf(point.x) * std::fabsf(point.x) + std::fabsf(point.y) * std::fabsf(point.y), 2);
			return (r >= 1) ? color1 : color2;
		}

	private:
		Color color1;
		Color color2;
	};

	class Checked : public Pattern {
	public:
		Checked(const Color& color1, const Color& color2) :
			color1(color1),
			color2(color2),
			Pattern()
		{}

		Color color_at(const Vec4& point) {

			float x = std::fabs(point.x);
			float y = std::fabs(point.y);
			float z = std::fabs(point.z);

			int sum = floorf(x) + floorf(y) + floorf(z);

			return sum % 2 == 0 ? color1 : color2;
		}

	private:
		Color color1;
		Color color2;
	};
	

	namespace Patterns {

		Striped* striped = new Striped(Color(1), Color(0));
		Ring* ringed = new Ring(Color(1), Color(0));
		Checked* checked = new Checked(Color(1), Color(0));

	}
}



#endif // INCLUDE_PATTERN_H
