#include <iostream>

#include "include/Color.h"
#include "include/World.h"
#include "include/Camera.h"
#include "include/Image_Buffer.h"
#include "include/Comps.h"

constexpr int NUM_RECURSIONS = 3;


namespace RayTracer {

    void UnitTestMatTranslation() {
        Vec4 p(-3, 4, 5, 1);
        Mat4 m = translate(5, -3, 2);
        Vec4 p_fin = m * p;
        Vec4 answer(2, 1, 7);
    }

	void UnitTestRayTransform() {
		Ray ray(Vec4(1, 2, 3, 1), Vec4(0, 1, 0));

		ray.transform(transform(3, 4, 5));

		Vec4 r_pos(4, 6, 8);
		Vec4 r_dir(0, 1, 0);
	}

    void UnitTestSphereTransform() {

        Sphere s(transform(0,0,0,1,1,1), &Materials::Obsidian);

        Ray ray(Vec4(0, 0, -5, 1), Vec4(0, 0, 1));
        Intersection i;

        s.intersection_test(i, ray);
        Vec4 position(ray.position(i.observation.t));
        __debugbreak();
    }

    void UnitTestMatVec() {

        UnitTestMatTranslation();
        UnitTestRayTransform();
        UnitTestSphereTransform();

        // Unit Test Mat4
        Vec4 p(1, 0, 1, 1);
        Mat4 A = rotate_x(PI / 2);
        Mat4 B = scale(5, 5, 5);
        Mat4 C = translate(10, 5, 7);

        Vec4 p2 = A * p;
        Vec4 p3 = B * p2;
        Vec4 p4 = C * p3;

        Vec4 pt5 = (C * B * A) * p;

        Vec4 correct(15, 0, 7);
    }
    
    void UnitTestTriangle() {

        Vec4 p1(0, 1, 0, 1);
        Vec4 p2(-1, 0, 0, 1);
        Vec4 p3(1, 0, 0, 1);

        Triangle triangle1(&p1, &p2, &p3, &Materials::Obsidian);

    }

}


void render(
    const int& i, const int& j, const int& width, const int& height,
    const RayTracer::World& localWorld, 
    const RayTracer::Camera& camera,
    RayTracer::Image_Buffer& image_buffer
    ) {

    int pixel_index = i * height + j;
    
    // Camera Ray
    float X = 2.0f * float(i) / float(width) - 1;
    float Y = -2.0f * float(j) / float(height) + 1;

    RayTracer::Ray ray = camera.getRay(X, Y);
    RayTracer::Intersection intersection;

    localWorld.intersection_test(intersection, ray);

    if (intersection.observation.hit != nullptr) {
        RayTracer::Comps comps = RayTracer::prepare_computations(intersection, ray);
        image_buffer[pixel_index] = localWorld.color_at(comps, NUM_RECURSIONS);
    }
    else {
        image_buffer[pixel_index] = localWorld.background_color;
    }

}


int main()
{
    //RayTracer::UnitTestMatVec();
    RayTracer::UnitTestTriangle();

    RayTracer::World world;
    RayTracer::Camera camera;
    RayTracer::Image_Buffer image;

    const int height = image.getHeight();
    const int width = image.getWidth();

    // enable parallel computing
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            render(i, j, width, height, world, camera, image);
        }
    }
    image.save();

}

