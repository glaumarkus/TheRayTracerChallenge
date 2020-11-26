#ifndef INCLUDE_TORUS_H
#define INCLUDE_TORUS_H

#include <cmath>
#include "hittable.h"


namespace RayTracer {

	namespace Utility {

		struct solution2 {
			float f[2] = { 0,0 };
		};
		struct solution3 {
			float f[3] = { 0,0,0 };
		};
		struct solution4 {
			float f[4] = { 0,0,0,0 };
		};

		struct coeffs2 {
			float f[3] = { 0,0,0 };
		};
		struct coeffs3 {
			float f[4] = { 0,0,0,0 };
		};

		struct coeffs4 {
			float f[5] = {0,0,0,0};
		};

		bool isZero(const float& f) { return (f < EPSILON&& f > -EPSILON); }

		bool solve2(const coeffs2& c, solution2& s) {

			float p = c.f[1] / (2 * c.f[2]);
			float q = c.f[0] / c.f[2];

			float det = p * p - q;

			if (det < 0) return false;

			if (isZero(det)) {
				solution2 s;
				s.f[0] = -p;
				s.f[1] = -p;
			}
			else {
				s.f[0] = std::sqrt(det);
				s.f[1] = -s.f[0];

			}
			return true;
		}

		bool solve3(const coeffs3& c, solution3& s) {

			float A = c.f[2] / c.f[3];
			float B = c.f[1] / c.f[3];
			float C = c.f[0] / c.f[3];

			float sq_A = A * A;
			float p = 1.0f / 3 * (-1.0f / 3 * sq_A + B);
			float q = 1.0 / 2 * (2.0 / 27 * A * sq_A - 1.0 / 3 * A * B + C);

			float cb_p = p * p * p;
			float D = q * q + cb_p;

			if (isZero(D)) {
				if (isZero(q)) /* one triple solution */ {
					s.f[0] = 0;
					s.f[1] = 0;
					s.f[2] = 0;
				}
				else /* one single and one double solution */ {
					float u = std::cbrtf(-q);
					s.f[0] = 2 * u;
					s.f[1] = -u;
					s.f[2] = -u;
				}
			}

			else if (D < 0) {
				float phi = 1.0f / 3 * acosf(-q / std::sqrt(-cb_p));
				float t = 2 * std::sqrt(-p);
				s.f[0] = t * cos(phi);
				s.f[1] = -t * cos(phi + PI / 3);
				s.f[2] = -t * cos(phi - PI / 3);
			}

			else {
				float sqrt_D = std::sqrt(D);
				float u = std::cbrt(sqrt_D - q);
				float v = -std::cbrt(sqrt_D + q);

				s.f[0] = u + v;
				s.f[1] = s.f[0];
				s.f[2] = s.f[0];
			}

			float sub = 1.0f / 3 * A;
			s.f[0] -= sub;
			s.f[1] -= sub;
			s.f[2] -= sub;

			return true;
		}

		bool solve4(const coeffs4& c, solution4& s4) {
			float A, B, C, D;
			A = c.f[3] / c.f[4];
			B = c.f[2] / c.f[4];
			C = c.f[1] / c.f[4];
			D = c.f[0] / c.f[4];

			float sq_A, p, q, r, s;
			sq_A = A * A;
			p = -3.0f / 8 * sq_A + B;
			q = 1.0f / 8 * sq_A * A - 1.0f / 2 * A * B + C;
			r = -3.0f / 256 * sq_A * sq_A + 1.0 / 16 * sq_A * B - 1.0 / 4 * A * C + D;

			// is zero
			if (r < EPSILON && r > -EPSILON) {
				coeffs3 coeff;
				coeff.f[0] = q;
				coeff.f[1] = p;
				coeff.f[2] = 0;
				coeff.f[3] = 1;

				solution3 s3;
				if (solve3(coeff, s3)) {
					s4.f[0] = s3.f[0];
					s4.f[1] = s3.f[1];
					s4.f[2] = s3.f[2];
					s4.f[3] = 0;

				}
				else return false;
			}
			else {
				coeffs3 coeff3;
				coeff3.f[0] = 1.0f / 2 * r * p - 1.0f / 8 * q * q;
				coeff3.f[1] = -r;
				coeff3.f[2] = -1.0f / 2 * p;
				coeff3.f[3] = 1;

				solution3 s3;
				if (solve3(coeff3, s3)) {

					float z = s3.f[0];
					float u = z * z - r;
					float v = 2 * z - p;

					if (u < EPSILON && u > -EPSILON)
						u = 0;
					else if (u > 0)
						u = std::sqrt(u);
					else
						return;

					if (v < EPSILON && v > -EPSILON)
						v = 0;
					else if (v > 0)
						v = std::sqrt(v);
					else
						return;

					coeffs2 coeff2_1;
					solution2 s2_1;

					coeffs2 coeff2_2;
					solution2 s2_2;

					coeff2_1.f[0] = z + u;
					coeff2_1.f[1] = q < 0 ? v : -v;
					coeff2_1.f[2] = 1.0f;

					coeff2_2.f[0] = z - u;
					coeff2_2.f[1] = q > 0 ? v : -v;
					coeff2_2.f[2] = 1.0f;

					if (solve2(coeff2_1, s2_1)) {
						s4.f[0] = s2_1.f[0];
						s4.f[1] = s2_1.f[1];

						if (solve2(coeff2_2, s2_2)) {
							s4.f[2] = s2_2.f[0];
							s4.f[3] = s2_2.f[1];
						}
						else {
							s4.f[2] = s2_1.f[0];
							s4.f[3] = s2_1.f[1];
						}

						
					}
					else if (solve2(coeff2_2, s2_2)) {
						s4.f[0] = s2_2.f[0];
						s4.f[1] = s2_2.f[1];
						s4.f[2] = s2_2.f[0];
						s4.f[3] = s2_2.f[1];
					}

					else {
						return false;
					}
				}
				else return false;
				
			}

			float sub = 1.0f / 4 * A;
			s4.f[0] -= sub;
			s4.f[1] -= sub;
			s4.f[2] -= sub;
			s4.f[3] -= sub;
		}
	}

	class Torus : public transformed {
	public:

		Torus(const Mat4& transformation, Material* material) :
			transformed(transformation, material)
		{}
		Torus(Mat4&& transformation, Material* material) :
			transformed(std::move(transformation), material)
		{}


	protected:

		void local_intersection_test(Intersection& i, const Ray& ray) {

			
			float sum_d_sqrd = dot(ray.direction, ray.direction);
			float e = dot(ray.origin, ray.origin);
			float f = dot(ray.origin, ray.direction);
			float four_a_sqrd = 4.0f * 1.0f * 1.0f;

			Utility::coeffs4 c;
			c.f[0] = e * e - four_a_sqrd * (1 - ray.origin.y * ray.origin.y);
			c.f[1] = 4.0f * f * e + 2.0f * four_a_sqrd * ray.origin.y * ray.direction.y;
			c.f[2] = 2.0f * sum_d_sqrd * e + 4.0f * f * f + four_a_sqrd * ray.direction.y * ray.direction.y;
			c.f[3] = 4.0f * sum_d_sqrd * f;
			c.f[4] = sum_d_sqrd * sum_d_sqrd;

			Utility::solution4 s4;
			// ray misses
			if (!Utility::solve4(c, s4)) return;
			
			for (int k = 0; k < 4; k++) {
				i.checkIntersection(s4.f[k], this);
			}

		}


		Vec4 local_normal_at(const Vec4& transformed_point) {

			constexpr float paramSquared = 2.0f;
			float pDots = dot(transformed_point, transformed_point);

			float x, y, z;
			x = 4.0f * transformed_point.x * (pDots - paramSquared);
			y = 4.0f * transformed_point.y * (pDots - paramSquared + 2);
			z = 4.0f * transformed_point.z * (pDots - paramSquared);

			return Vec4(x, y, z).normalize();
		}


	};



}




#endif