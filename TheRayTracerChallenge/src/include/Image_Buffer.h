#ifndef INCLUDE_IMAGE_BUFFER
#define INCLUDE_IMAGE_BUFFER

#include <fstream>
#include <sstream>
#include <string>

#include "Color.h"

// save
namespace RayTracer {

    class Image_buffer {
    public:

        Image_buffer(int width, int height) :
            width(width),
            height(height)
        {
            pixel_color = new Color[width * height];
        }


        void save(const std::string& filename = "image.ppm") {
            
            std::string prefix = "../../images/";
            prefix.append(filename);

            std::ofstream out(prefix);
            out << "P3\n" << width << " " << height << "\n255\n";
            for (int j = width - 1; j >= 0; j--) {
                for (int i = 0; i < height; i++) {
                    int pixel_index = j * width + i;
                    int ir = int(255.99 * pixel_color[pixel_index].r);
                    int ig = int(255.99 * pixel_color[pixel_index].g);
                    int ib = int(255.99 * pixel_color[pixel_index].b);
                    out << ir << " " << ig << " " << ib << "\n";
                }
            }

        }


    private:
        int width, height;
        Color* pixel_color;

    };

}


#endif // !INCLUDE_IMAGE_BUFFER
