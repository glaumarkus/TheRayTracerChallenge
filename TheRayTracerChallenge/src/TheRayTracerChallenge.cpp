#include <iostream>

#include "include/Color.h"
#include "include/World.h"
#include "include/Camera.h"
#include "include/Image_Buffer.h"
#include "include/Comps.h"

constexpr int NUM_RECURSIONS = 3;


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

