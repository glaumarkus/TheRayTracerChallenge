#include <iostream>

#include "include/Sphere.h"


int main()
{
    
    //RayTracer::hittable* hitptr = new RayTracer::Sphere(RayTracer::Mat4(), &RayTracer::Materials::Brass);

    RayTracer::hittable* pt = new RayTracer::Sphere(RayTracer::scale(1,1,1), &RayTracer::Materials::Brass);
    //RayTracer::hittable* pt2 = pt;

    RayTracer::Sphere s(RayTracer::Mat4(), &RayTracer::Materials::Brass);

    RayTracer::Ray ray(RayTracer::Vec4(-5, 0, 0), RayTracer::Vec4(1, 0, 0));
    RayTracer::Intersection i;

    pt->intersection_test(i, ray);
    RayTracer::Vec4 pt_of_intersection = pt->normal_at(ray.position(i.observation.t));



    std::cout << "Hello World!\n";
}

