#include <iostream>
#include <chrono>
#include <string>

#include "include/Color.h"
#include "include/World.h"
#include "include/Camera.h"
#include "include/Image_Buffer.h"
#include "include/Comps.h"

#include "include/OBJ_Reader.h"

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

	void UnitTestCube() {


        Ray ray(Vec4(5,0.5,0, 1), Vec4(-1,0,0));
        Cube c(Mat4(), &Materials::Brass);
        Intersection i;
        c.intersection_test(i, ray);
        i = Intersection();

        Vec4 normal = c.normal_at(ray.position(i.observation.t),0,0);

        ray = Ray(Vec4(-2, 0, 0), Vec4(0.2673, 0.5345, 0.8018));
        //Cube c(transform(0,-1,-1,0.5f,0.5f,0.5f), &Materials::Brass);

        // Normal Test
        Vec4 n1 = c.normal_at(Vec4(1, 0.5, -0.8, 1),0,0);
        Vec4 n2 = c.normal_at(Vec4(-0.4, 1, -0.1, 1), 0, 0);
        Vec4 n3 = c.normal_at(Vec4(0.3, -1, -0.7, 1), 0, 0);
        Vec4 n4 = c.normal_at(Vec4(1, 1, 1, 1), 0, 0);
        Vec4 n5 = c.normal_at(Vec4(-1, -1, -1, 1), 0, 0);

	}

    void UnitTestPattern() {
        

        Vec4 p1(0, 0, 0);
		Vec4 p2(0, 1, 0);
		Vec4 p3(0, 2, 0);
		Vec4 p4(1, 0.5, 0);
		Vec4 p5(2, 1.7, 0);

        Color t(0);
        t = Patterns::striped->color_at(p1);
        t = Patterns::striped->color_at(p2);
        t = Patterns::striped->color_at(p3);
        t = Patterns::striped->color_at(p4);
        t = Patterns::striped->color_at(p5);




    }

    void UnitTestGroup() {

        Group g(&Materials::Gold);
        
		Sphere* s1 = new Sphere(std::move(g.get_transformation()), g.getMaterial());
        g.add_child(s1);


    }

    void UnitTestReader() {

        std::string obj_file = "objects/Dragon.obj";
        OBJ_Reader reader(obj_file, &Materials::Gold, std::move(Matrix::Default_Matrix));
        Group g(&Materials::Gold);
        reader.copy_data(g);

    }

}

namespace Utility {

    class timer {
    public:
        timer() {    
            start = std::chrono::high_resolution_clock::now();
        }
        void get_time(const std::string& msg) {
			auto end = std::chrono::high_resolution_clock::now();
			auto start_ts = std::chrono::time_point_cast<std::chrono::milliseconds> (start).time_since_epoch().count();
			auto end_ts = std::chrono::time_point_cast<std::chrono::milliseconds> (end).time_since_epoch().count();
			float duration = (float)end_ts - (float)start_ts;
			std::cout << msg << " took " << duration << " milliseconds.\n";
        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start;  
    };
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
    //RayTracer::UnitTestCube();
    //RayTracer::UnitTestPattern();
    //RayTracer::UnitTestGroup();
    //RayTracer::UnitTestReader();
    

    Utility::timer t;

    RayTracer::World world;
    RayTracer::Camera camera;
    RayTracer::Image_Buffer image;
    
    t.get_time("Loading World");

    const int height = image.getHeight();
    const int width = image.getWidth();

    // enable parallel computing
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            render(i, j, width, height, world, camera, image);
        }
    }

    t.get_time("Render");

    image.save();
    t.get_time("Save");
    

}

