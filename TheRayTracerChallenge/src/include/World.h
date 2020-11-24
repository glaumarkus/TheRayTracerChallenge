#ifndef INCLUDE_WORLD_H
#define INCLUDE_WORLD_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Comps.h"

#include "hittable.h"
#include "Sphere.h"
#include "Plane.h"
#include "Cube.h"
#include "Triangle.h"

#include "Lights.h"

namespace RayTracer {

	class World {
	public:
		// default world
		World();
		World(std::string&& filename);

		~World();

		void intersection_test(Intersection& intersection, const Ray& ray) const;
		Color color_at(const Comps& comps, int num_recursions) const;

		Color background_color = Color(0);

	private:

		Color lighting_model(const Comps& comps, const Light* light, const float& shade_intensity) const;
		float shade_intensity_at(const Comps& comps, const Light* light) const;
		Color reflection_at(const Comps& comps, int num_recursions) const;
		Color refraction_at(const Comps& comps, int num_recursions) const;

		

		std::vector <hittable*> hittable_objects;
		std::vector <Light*> light_objects;

	};


	// default world
	World::World() {

		/*
		Light* light = new Light(Color(0.9f), Vec4(-50, 50, 50, 1));
		light_objects.push_back(light);
		*/
		SphereLight* light_sphere = new SphereLight(Color(0.9f), Vec4(-50, 50, 50, 1), 10, 5.0f);
		light_objects.push_back(light_sphere);

		Sphere* s1 = new Sphere(transform(-6.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), &Materials::Emerald);
		hittable_objects.push_back(s1);

		
		Sphere* s2 = new Sphere(scale(5.0f, 5.0f, 5.0f), &Materials::Gold);
		hittable_objects.push_back(s2);

		
		/*
		
		Light* light1 = new Light(Color(1.0f), Vec4(50, 100, -50));
		Light* light2 = new Light(Color(0.2f), Vec4(-400, 50, -10));
		Material white_mat( Color(0.7f), Color(0.1f), Color(0.0f), 0.1f, 0.0f, 1.0f);

		*/

	}

	// TODO: implement reader
	World::World(std::string&& filename) {
	}

	World::~World() {
		for (auto obj : hittable_objects) {
			delete obj;
		}
	}



	void World::intersection_test(Intersection& intersection, const Ray& ray) const {
		for (const auto obj : hittable_objects) {
			obj->intersection_test(intersection, ray);
		}
	}


	Color World::color_at(const Comps& comps, int num_recursions) const {

		Color pixel_color;

		// calculate shade intensity
		float shade_intensity = 0.0f;
		int num_lights = light_objects.size();
		for (const auto& light : light_objects) {
			shade_intensity += shade_intensity_at(comps, light);
		}
		shade_intensity /= num_lights;

		// diffuse and specular for every light source
		for (const auto& light : light_objects) {
			pixel_color += lighting_model(comps, light, shade_intensity);
		}

		// reflection & refraction
		if (comps.material->reflective > 0.0f && num_recursions >= 0) {
			Color reflection_color = reflection_at(comps, num_recursions);
		}

		if (comps.material->transparent > 0.0f && num_recursions >= 0) {
			Color refraction_color = refraction_at(comps, num_recursions);
		}

		pixel_color /= (float)num_lights;

		return pixel_color;

	}

	Color World::lighting_model(const Comps& comps, const Light* light, const float& shade_intensity) const {

		Color lighted_color = comps.material->ambient * light->intensity;

		Vec4 light_vector = (light->position - comps.point).normalize();
		float lightDotNormal = dot(light_vector, comps.normal_vector);

		if (lightDotNormal > 0) {

			lighted_color += comps.material->diffuse * lightDotNormal * shade_intensity;

			float reflectDotEye = dot(comps.reflect_vector, light_vector);
			if (reflectDotEye > 0 && shade_intensity > 0.0f) {
				float factor = std::pow(reflectDotEye, comps.material->shinyness);
				if (factor > 0.5f) 
					int x = 0;
				lighted_color += light->intensity * comps.material->specular * factor;
			}
		}
		lighted_color.clamp();
		return lighted_color;
	}



	float World::shade_intensity_at(const Comps& comps, const Light* light) const {

		int count = 0;
		int size = light->light_points.size();

		for (const Vec4& light_point : light->light_points) {

			Vec4 shade_vector = light_point - comps.over_point;
			shade_vector.w = 0.0f;
			float distance = shade_vector.length();
			shade_vector.norm(distance);

			Ray shade_ray(comps.over_point, shade_vector);
			Intersection shade_intersection;

			intersection_test(shade_intersection, shade_ray);

			if (shade_intersection.observation.t > distance) count++;

		}

		return (float)count / (float)size;

	}

	Color World::reflection_at(const Comps& comps, int num_recursions) const {

		Color reflection_color(0);

		Ray reflection_ray(comps.over_point, comps.reflect_vector);
		Intersection reflection_intersection;

		intersection_test(reflection_intersection, reflection_ray);

		if (reflection_intersection.observation.hit != nullptr) {
			Comps comps = prepare_computations(reflection_intersection, reflection_ray);
			reflection_color = color_at(comps, --num_recursions);
		}
		return reflection_color;
	}

	Color World::refraction_at(const Comps& comps, int num_recursions) const {

		Color refraction_color(0);

		float n1 = 1.0f;
		float n2 = comps.material->refractive;

		float n_ratio = n1 / n2;
		float cos_i = dot(comps.eye_vector, comps.normal_vector);
		float sin2_t = n_ratio * n_ratio * (1 - cos_i + cos_i);
		if (sin2_t > 1.0f) return refraction_color;

		float cos_t = std::sqrt(1.0f - sin2_t);
		Vec4 refraction_direction = comps.normal_vector * (n_ratio * cos_i - cos_t) - comps.eye_vector * n_ratio;

		Ray refraction_ray(comps.under_point, refraction_direction);
		Intersection refraction_intersection;

		intersection_test(refraction_intersection, refraction_ray);

		if (refraction_intersection.observation.hit != nullptr) {
			Comps comps = prepare_computations(refraction_intersection, refraction_ray);
			refraction_color = color_at(comps, --num_recursions);
		}
		return refraction_color;
	}


 
}





#endif // !INCLUDE_WORLD_H
