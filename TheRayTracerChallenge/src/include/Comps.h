#ifndef COMPS_HPP
#define COMPS_HPP

#include "Intersection.h"
#include "hittable.h"

#include <list>

namespace RayTracer {

	struct Comps {

		float t;
		Vec4 point;
		Vec4 under_point;
		Vec4 over_point;
		Vec4 local_point;

		Vec4 eye_vector;
		Vec4 normal_vector;
		Vec4 reflect_vector;
		Vec4 refract_vector;

		bool inside;
		Material* material;

		float n1;
		float n2;
		
	};

	void check_container(std::list<Observation>& l, const Observation& obs) {

		for (auto it = l.begin(); it != l.end(); it++) {
			if (it->hit == obs.hit) {
				l.erase(it);
				return;
			}
		}
		l.push_back(obs);
	}

	void get_n1n2(const Intersection& intersection, Comps& comps) {

		// first start by sorting intersection list
		std::list<Observation> cpy = intersection.observations;
		cpy.sort();

		std::list<Observation>::iterator it;
		std::list<Observation> tmp;

		// for each observation in list

		for (it = cpy.begin(); it != cpy.end(); it++) {

			if (it->hit == intersection.observation.hit) {

				if (tmp.size() == 0) {
					comps.n1 = 1.0f;
				}
				else {
					std::list<Observation>::iterator last = it;
					last--;
					comps.n1 = last->hit->getMaterial()->refractive;
				}
			}

			check_container(tmp, *it);

			if (it->hit == intersection.observation.hit) {

				if (tmp.size() == 0) {
					comps.n2 = 1.0f;
				}
				else {
					std::list<Observation>::iterator last = tmp.end();
					last--;
					comps.n2 = last->hit->getMaterial()->refractive;
				}

				return;
			}
		}

		std::cout << "n1: " << comps.n1 << "\tn2: " << comps.n2 << "\n";
	}

	

	Comps prepare_computations(const Intersection& intersection, const Ray& ray) {

		Comps comps;

        comps.t = intersection.observation.t;
        comps.point = ray.position(comps.t);
		comps.normal_vector = intersection.observation.hit->normal_at(comps.point, intersection.observation.u, intersection.observation.v);
		comps.under_point = comps.point - EPSILON * comps.normal_vector;
		comps.over_point = comps.point + EPSILON * comps.normal_vector;
		comps.eye_vector = ray.direction * -1;
        comps.material = intersection.observation.hit->getMaterial();
		comps.local_point = intersection.observation.hit->getLocalPoint(comps.point);
		//comps.hit = intersection.observation.hit;

		comps.reflect_vector = reflect(ray.direction, comps.normal_vector);

		if (comps.material->transparent > 0.0f) {
			get_n1n2(intersection, comps);
		}

		float nDotE = dot(comps.normal_vector, comps.eye_vector);
		if (nDotE < 0) comps.normal_vector = comps.normal_vector * -1;

		return comps;
	}


}







#endif 