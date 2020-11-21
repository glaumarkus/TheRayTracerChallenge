#ifndef INCLUDE_COLOR_HPP
#define INCLUDE_COLOR_HPP

namespace RayTracer {


	class Color {
	public:

		Color() :
			r(0.0f),
			g(0.0f),
			b(0.0f)
		{
			a = 0.0f;
		};

		Color(float l) :
			r(l),
			g(l),
			b(l)
		{
			a = 0.0f;
		};

		Color(float r, float g, float b) :
			r(r),
			g(g),
			b(b)
		{
			a = 0.0f;
		};

		Color(float r, float g, float b, float a) :
			r(r),
			g(g),
			b(b),
			a(a)
		{};

		float getTransparency() {
			return a;
		}

		void clamp() {
			r = r > 0.0f ? (r > 1 ? 1.0f : r) : 0.0f;
			g = g > 0.0f ? (g > 1 ? 1.0f : g) : 0.0f;
			b = b > 0.0f ? (b > 1 ? 1.0f : b) : 0.0f;
			a = a > 0.0f ? (a > 1 ? 1.0f : a) : 0.0f;
		}

		Color& operator =(const Color& c) {
			r = c.r;
			g = c.g;
			b = c.b;
			a = c.a;
			return *this;
		}

		Color& operator +=(const Color& c) {
			r += c.r;
			g += c.g;
			b += c.b;
			return *this;
		}

		Color& operator *=(const Color& c) {
			r *= c.r;
			g *= c.g;
			b *= c.b;
			return *this;
		}

		Color& operator *=(float f) {
			r *= f;
			g *= f;
			b *= f;
			return *this;
		}

		float r, g, b, a;

	};


	inline Color operator +(const Color& c1, const Color& c2)
	{
		return Color(c1.r + c2.r,
			c1.g + c2.g,
			c1.b + c2.b);
	}

	inline Color operator *(const Color& c1, const Color& c2)
	{
		return Color(c1.r * c2.r,
			c1.g * c2.g,
			c1.b * c2.b);
	}

	inline Color operator *(const Color& c, float f)
	{
		return Color(c.r * f,
			c.g * f,
			c.b * f);
	}

	inline Color operator *(float f, const Color& c)
	{
		return Color(f * c.r,
			f * c.g,
			f * c.b);
	}


}


#endif 