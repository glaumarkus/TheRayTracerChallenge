#ifndef INCLUDE_VEC4_H
#define INCLUDE_VEC4_H

#include <cmath>
#include <iostream>

// RayTracer namespace
namespace RayTracer {

constexpr float PI = 3.1415926f;
constexpr float EPSILON = 0.0001f;
constexpr float INF = 100000.0f;


struct Vec4 {

	// vars
	float x, y, z, w;

	void print() { printf("Vector: (%f, %f, %f, %f)\n", x, y, z, w); }

	// default constructors
	Vec4() {
		x = 1.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	Vec4(const float& x, const float& y, const float& z) :
		x(x),
		y(y),
		z(z),
		w(0.0f)
	{}

	Vec4(const float& x, const float& y, const float& z, const float& w) :
		x(x),
		y(y),
		z(z),
		w(w) 
	{}

	~Vec4() {}

	// copy constructor
	Vec4(const Vec4& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}
	
	// move constructor
	Vec4( Vec4&& other) noexcept {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	inline float length2() { return x * x + y * y + z * z + w * w; }

	inline float length() {	return std::sqrt(length2()); }

	Vec4& normalize() {
		norm();
		return *this;
	}

	void norm() {
		float oneOverLength = 1.f / length();
		x *= oneOverLength;
		y *= oneOverLength;
		z *= oneOverLength;
		w *= oneOverLength;
	}


	// operators
	Vec4& operator =(const Vec4& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	Vec4 operator =(const Vec4& other) const {
		return Vec4(other.x, other.y, other.z, other.w);
	}

	Vec4& operator =(Vec4&& other) noexcept {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	Vec4 operator =(Vec4&& other) const {
		return Vec4(other.x, other.y, other.z, other.w);
	}

	Vec4& operator +=(const Vec4& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	Vec4& operator -=(const Vec4& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}
	Vec4& operator *=(float f) {
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return *this;
	}
	Vec4& operator /=(float f) {
		x /= f;
		y /= f;
		z /= f;
		w /= f;
		return *this;
	}

	float operator [](const int& idx) {
		if (idx == 0) return x;
		else if (idx == 1) return y;
		else if (idx == 2) return z;
		else if (idx == 3) return w;
		else return 0.0f;
	}

	float operator [](const int& idx) const {
		if (idx == 0) return x;
		else if (idx == 1) return y;
		else if (idx == 2) return z;
		else if (idx == 3) return w;
		else return 0.0f;
	}

};


// add operators
inline Vec4 operator +(const Vec4& v1, const Vec4& v2)
{
	return Vec4(v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z,
		v1.w + v2.w);
}

inline Vec4 operator -(const Vec4& v1, const Vec4& v2)
{
	return Vec4(v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z,
		v1.w - v2.w);
}

inline Vec4 operator *(const Vec4& v1, const Vec4& v2)
{
	return Vec4(v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z,
		v1.w * v2.w);
}

inline Vec4 operator *(const Vec4& v, float f)
{
	return Vec4(v.x * f,
		v.y * f,
		v.z * f,
		v.w * f);
}

inline Vec4 operator *(float f, const Vec4& v)
{
	return Vec4(f * v.x,
		f * v.y,
		f * v.z,
		f * v.w);
}

inline Vec4 operator /(const Vec4& v1, const Vec4& v2)
{
	return Vec4(v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z,
		v1.w / v2.w);
}

inline Vec4 operator /(const Vec4& v, float f)
{
	return Vec4(v.x / f,
		v.y / f,
		v.z / f,
		v.w / f);
}

inline Vec4 operator /(float f, const Vec4& v)
{
	return Vec4(f / v.x,
		f / v.y,
		f / v.z,
		f / v.w);
}


// Vector operations

// dot
float dot(const Vec4& v1, const Vec4& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

// cross
Vec4 cross(const Vec4& v1, const Vec4& v2) {
	return
		Vec4(v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
}

// reflect
Vec4 reflect(const Vec4& v1, const Vec4& v2) {
	return Vec4(v1 - v2 * 2.0f * dot(v1, v2));
}

// basic operations

bool equal(const float& f1, const float& f2) {
	if (std::abs(f1 - f2) < EPSILON)
		return true;
	return false;
}

struct Point : public Vec4 {

	// default constructors
	Point() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}

	Point(const float& xIN, const float& yIN, const float& zIN) {
		x = xIN;
		y = yIN;
		z = zIN;
		w = 1.0f;
	}

};


}

#endif