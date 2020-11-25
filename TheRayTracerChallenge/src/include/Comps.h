#ifndef COMPS_HPP
#define COMPS_HPP

#include "Intersection.h"
#include "hittable.h"


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
		

	};

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
		//comps.refract_vector

		float nDotE = dot(comps.normal_vector, comps.eye_vector);

		if (nDotE < 0) comps.normal_vector = comps.normal_vector * -1;

		return comps;
	}


}







#endif 