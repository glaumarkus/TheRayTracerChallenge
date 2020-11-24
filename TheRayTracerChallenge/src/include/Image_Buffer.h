#ifndef INCLUDE_IMAGE_BUFFER
#define INCLUDE_IMAGE_BUFFER

#include <fstream>
#include <sstream>
#include <string>

#include "Color.h"

// save
namespace RayTracer {

    class Image_Buffer {
    public:

        Image_Buffer() :
            width(200),
            height(200)
        {
            int num_pixel = width * height;
            pixel_color = new Color[num_pixel];
        }

        Image_Buffer(int width, int height) :
            width(width),
            height(height)
        {
            int num_pixel = width * height;
            pixel_color = new Color[num_pixel];
        }


        Color& operator [](const int& idx) {
            return pixel_color[idx];
        }

        void save(const std::string& filename = "image.ppm") {
            
            std::string prefix = "images/";
            prefix.append(filename);

            std::ofstream out(prefix);
            out << "P3\n" << width << " " << height << "\n255\n";
            for (int j = 0; j < height; j++) {
                for (int i = 0; i < width; i++) {
                    int pixel_index = j * height + i;
                    int ir = int(255.99 * pixel_color[pixel_index].r);
                    int ig = int(255.99 * pixel_color[pixel_index].g);
                    int ib = int(255.99 * pixel_color[pixel_index].b);
                    out << ir << " " << ig << " " << ib << "\n";
                }
            }


        }

        int getWidth() const { return width; }
        int getHeight() const { return height; }


    private:
        int width, height;
        Color* pixel_color;

    };

}


#endif // !INCLUDE_IMAGE_BUFFER
