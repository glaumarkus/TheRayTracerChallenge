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
#include "Group.h"
#include "OBJ_Reader.h"

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


		SphereLight* light_sphere = new SphereLight(Color(0.9f), Vec4(-50, -50, 50, 1), 10, 5.0f);
		light_objects.push_back(light_sphere);

		//Group* g = new Group(&Materials::Brass);

		//Sphere* s1 = new Sphere(transform(3.0f, -2.0f, 0.5f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), &Materials::Gold);
		//Sphere* s2 = new Sphere(scale(5.0f, 5.0f, 5.0f), &Materials::Reflective_Chrome);

		/*

		Sphere* s1 = new Sphere(transform(6.0f, 0.0f, 0.0f, 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), &Materials::Reflective_Chrome);
		Sphere* s2 = new Sphere(transform(-6.0f, 0.0f, 0.0f, 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), &Materials::Glass);
		Sphere* s3 = new Sphere(Matrix::Default_Matrix, &Materials::Gold);
		Group* g = new Group(&Materials::Brass);


		hittable_objects.push_back(s1);
		hittable_objects.push_back(s2);
		hittable_objects.push_back(s3);
		*/
		/*
		g->add_child(s1);
		g->add_child(s2);
		g->set_bounds();
		hittable_objects.push_back(g);
		*/

		Material* temp = new Material(Color(0.05, 0.05, 0.05), Color(0), Color(0.8), 200.0f, 0.0f, 1.0f, 1.0f);
		//Material* temp2 = new Material(Color(0), Color(0), Color(0), 0.0f, 1.0f, 0.0f, 1.0f);

		Sphere* s1 = new Sphere(transform(0, -5, 0, 4, 4, 4), temp);
		//Sphere* s2 = new Sphere(transform(0, -5, 0, 1, 1, 1), temp2);

		Plane* p = new Plane(rotate_x(-PI / 2), &Materials::Checkboard);
		hittable_objects.push_back(p);
		hittable_objects.push_back(s1);
		//hittable_objects.push_back(s2);

		/*

		//std::string obj_file = "objects/Dragon.obj";
		std::string obj_file = "objects/teapot.obj";
		//OBJ_Reader reader(obj_file, &Materials::Gold, transform(0,0,0,2.5,2.5,2.5));
		OBJ_Reader reader(obj_file, &Materials::Gold, std::move(scale(0.5,0.5,0.5)));
		Group* g = new Group(translate(0,0,-3),&Materials::Gold);
		reader.copy_data(*g);
		hittable_objects.push_back(g);
		*/
		/*
		Plane* p1 = new Plane(transform(0, 0, -5,1,1,1,-PI/2), &Materials::Stripes);
		hittable_objects.push_back(p1);
		
		Sphere* s1 = new Sphere(transform(6.0f, 0.0f, 0.0f, 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), &Materials::Gold);
		hittable_objects.push_back(s1);
		*/
		//Sphere* s2 = new Sphere(scale(5.0f, 5.0f, 5.0f), &Materials::Gold);
		//hittable_objects.push_back(s2);
		
		/*
		Cube* c1 = new Cube(transform(
			2.4,2.4,2.4,
			0.6, 0.6, 0.6,
			0,0,-PI/3), &Materials::Emerald);
		Cube* c2 = new Cube(transform(
			2.4, -2.4, -2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Brass);
		Cube* c3 = new Cube(transform(
			2.4, -2.4, 2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Obsidian);
		Cube* c4 = new Cube(transform(
			2.4, 2.4, -2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Gold);
		Cube* c5 = new Cube(transform(
			2.4, 0, -2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Emerald);
		Cube* c6 = new Cube(transform(
			2.4, 0, 2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Brass);
		Cube* c7 = new Cube(transform(
			2.4, 0, 0,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Obsidian);
		Cube* c8 = new Cube(transform(
			2.4, 2.4, 0,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Chrome);
		Cube* c9 = new Cube(transform(
			2.4, -2.4, 0,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Gold);

		Cube* c10 = new Cube(transform(
			0, 2.4, 2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Emerald);
		Cube* c11 = new Cube(transform(
			0, -2.4, -2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Brass);
		Cube* c12 = new Cube(transform(
			0, -2.4, 2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Obsidian);
		Cube* c13 = new Cube(transform(
			0, 2.4, -2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Gold);
		Cube* c14 = new Cube(transform(
			0, 0, -2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Emerald);
		Cube* c15 = new Cube(transform(
			0, 0, 2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Brass);
		Cube* c16 = new Cube(transform(
			0, 0, 0,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Obsidian);
		Cube* c17 = new Cube(transform(
			0, 2.4, 0,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Chrome);
		Cube* c18 = new Cube(transform(
			0, -2.4, 0,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Gold);


		Cube* c19 = new Cube(transform(
			-2.4, 2.4, 2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Emerald);
		Cube* c20 = new Cube(transform(
			-2.4, -2.4, -2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Brass);
		Cube* c21 = new Cube(transform(
			-2.4, -2.4, 2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Obsidian);
		Cube* c22 = new Cube(transform(
			-2.4, 2.4, -2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Gold);
		Cube* c23 = new Cube(transform(
			-2.4, 0, -2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Emerald);
		Cube* c24 = new Cube(transform(
			-2.4, 0, 2.4,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Brass);
		Cube* c25 = new Cube(transform(
			-2.4, 0, 0,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Obsidian);
		Cube* c26 = new Cube(transform(
			-2.4, 2.4, 0,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Chrome);
		Cube* c27 = new Cube(transform(
			-2.4, -2.4, 0,
			0.6, 0.6, 0.6,
			0, 0, -PI / 3), &Materials::Gold);



		hittable_objects.push_back(c1);
		hittable_objects.push_back(c2);
		hittable_objects.push_back(c3);
		hittable_objects.push_back(c4);
		hittable_objects.push_back(c5);
		hittable_objects.push_back(c6);
		hittable_objects.push_back(c7);
		hittable_objects.push_back(c8);
		hittable_objects.push_back(c9);

		hittable_objects.push_back(c10);
		hittable_objects.push_back(c11);
		hittable_objects.push_back(c12);
		hittable_objects.push_back(c13);
		hittable_objects.push_back(c14);
		hittable_objects.push_back(c15);
		hittable_objects.push_back(c16);
		hittable_objects.push_back(c17);
		hittable_objects.push_back(c18);

		hittable_objects.push_back(c19);
		hittable_objects.push_back(c20);
		hittable_objects.push_back(c21);
		hittable_objects.push_back(c22);
		hittable_objects.push_back(c23);
		hittable_objects.push_back(c24);
		hittable_objects.push_back(c25);
		hittable_objects.push_back(c26);
		hittable_objects.push_back(c27);
		*/

	}

	// TODO: implement reader
	World::World(std::string&& filename) {

		/*

		Sphere* s1 = new Sphere(scale(2, 2, 2), &Materials::Glass);
		Sphere* s2 = new Sphere(translate(0, 0, -0.25f), &Materials::Water);
		Sphere* s3 = new Sphere(translate(0, 0, 0.25f), &Materials::Diamond);

		hittable_objects.push_back(s1);
		hittable_objects.push_back(s2);
		hittable_objects.push_back(s3);

		*/

		/*
		Material temp(Color(0,0,0), Color(0), Color(0), 0.0f, 0.0f,0.5f, 1.5f);
		Material temp2(Color(0.5, 0, 0), Color(0), Color(0),0.0f);

		Plane* p = new Plane(translate(0, -1, 0), &temp);
		Sphere* s = new Sphere(translate(0, -3.5, -0.5), &temp2);

		hittable_objects.push_back(p);
		hittable_objects.push_back(s);
		*/
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


	Color World::color_at(const Comps& comps, const int num_recursions) const {

		Color pixel_color;
		Color reflection_color;
		Color refraction_color;

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
			reflection_color = reflection_at(comps, num_recursions);
			pixel_color += reflection_color;
		}

		if (comps.material->transparent > 0.0f && num_recursions >= 0) {
			refraction_color = refraction_at(comps, num_recursions);
			pixel_color += refraction_color;
		}

		pixel_color /= (float)num_lights;
		pixel_color.clamp();

		return pixel_color;

	}

	Color World::lighting_model(const Comps& comps, const Light* light, const float& shade_intensity) const {

		Color lighted_color = light->intensity;

		if (comps.material->pattern == nullptr)
			lighted_color *= comps.material->ambient;
		else
			lighted_color *= comps.material->pattern->color_at(comps.local_point);

		const Vec4 light_vector = (light->position - comps.point).normalize();
		const float lightDotNormal = dot(light_vector, comps.normal_vector);

		if (lightDotNormal > 0) {

			lighted_color += comps.material->diffuse * lightDotNormal * shade_intensity;

			const float reflectDotEye = dot(comps.reflect_vector, light_vector);
			if (reflectDotEye > 0 && shade_intensity > 0.0f) {
				const float factor = std::pow(reflectDotEye, comps.material->shinyness);
				lighted_color += light->intensity * comps.material->specular * factor;
			}
		}
		//lighted_color.clamp();
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

		const Ray reflection_ray(comps.over_point, comps.reflect_vector);
		Intersection reflection_intersection;

		intersection_test(reflection_intersection, reflection_ray);

		if (reflection_intersection.observation.hit != nullptr) {
			const Comps reflection_comps = prepare_computations(reflection_intersection, reflection_ray);
			reflection_color = color_at(reflection_comps, num_recursions - 1);
		}
		return reflection_color * comps.material->reflective;
	}

	Color World::refraction_at(const Comps& comps, const int num_recursions) const {

		Color refraction_color(0);

		const float n_ratio = comps.n1 / comps.n2;
		const float cos_i = dot(comps.eye_vector, comps.normal_vector);
		const float sin2_t = n_ratio * n_ratio * (1 - cos_i + cos_i);
		if (sin2_t > 1.0f) return refraction_color;

		const float cos_t = std::sqrt(1.0f - sin2_t);
		const Vec4 refraction_direction = ((comps.normal_vector * -1) * (n_ratio * cos_i - cos_t) - (comps.eye_vector) * n_ratio).normalize();

		const Ray refraction_ray(comps.under_point, refraction_direction);
		Intersection refraction_intersection;

		intersection_test(refraction_intersection, refraction_ray);

		if (refraction_intersection.observation.hit != nullptr) {
			const Comps refraction_comps = prepare_computations(refraction_intersection, refraction_ray);
			refraction_color = color_at(refraction_comps, num_recursions - 1);
		}
		return refraction_color * comps.material->transparent;
	}


 
}





#endif // !INCLUDE_WORLD_H
