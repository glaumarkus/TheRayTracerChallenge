#ifndef INCLUDE_MATERIAL_H
#define INCLUDE_MATERIAL_H

#include "Color.h"
#include "Pattern.h"

namespace RayTracer {


    class Material {
    public:

        Material() :
            ambient(Color(0.5f)),
            diffuse(Color(0.8f)),
            specular(Color(0.9f)),
            shinyness(20),
            reflective(0.0f),
            transparent(0.0f),
            refractive(1.0f),
            pattern(nullptr)
        {}

        Material(const Color& ambient, const Color& diffuse, const Color& specular, const float& shinyness) :
            ambient(ambient),
            diffuse(diffuse),
            specular(specular),
            shinyness(shinyness),
            reflective(0.0f),
            transparent(0.0f),
			refractive(1.0f), 
			pattern(nullptr)
        {}

        Material(const Color& ambient, const Color& diffuse, const Color& specular, const float& shinyness, const float& reflective, const float& transparent, const float& refractive) :
            ambient(ambient),
            diffuse(diffuse),
            specular(specular),
            shinyness(shinyness),
            reflective(reflective),
            transparent(transparent),
			refractive(refractive),
			pattern(nullptr)
        {}

		Material(const Color& ambient, const Color& diffuse, const Color& specular, const float& shinyness, const float& reflective, const float& transparent, const float& refractive, Pattern* patternIN) :
			ambient(ambient),
			diffuse(diffuse),
			specular(specular),
			shinyness(shinyness),
			reflective(reflective),
			transparent(transparent),
			refractive(refractive),
			pattern(patternIN)
		{}

        Material(const float& ambientF, const float& diffuseF, const float& specularF, const float& shinyness) :
            ambient(Color(ambientF)),
            diffuse(Color(diffuseF)),
            specular(Color(specularF)),
            shinyness(shinyness),
            reflective(0.0f),
            transparent(0.0f),
			refractive(1.0f),
			pattern(nullptr)
        {}

        Material(const Material& other) {
            ambient = other.ambient;
            diffuse = other.diffuse;
            specular = other.specular;
            shinyness = other.shinyness;
            reflective = other.reflective;
            transparent = other.transparent;
            refractive = other.refractive;
        }

        ~Material() {
            //delete pattern;
        }




        Material& operator =(const Material& other) {
            ambient = other.ambient;
            diffuse = other.diffuse;
            specular = other.specular;
            shinyness = other.shinyness;
            reflective = other.reflective;
            transparent = other.transparent;
            refractive = other.refractive;
            return *this;
        }

        Pattern* pattern;

        Color ambient;
        Color diffuse;
        Color specular;

        float shinyness;
        float reflective;
        float transparent;
        float refractive;



        // texture specific
        /*
        Texture* texture;
        int mapA = 0;
        int mapD = 0;
        int mapS = 0;
        int mapTransparent = 0;
        */

        /*
        Vacuum: 1
        Air: 1.00029
        Water: 1.333
        Glass: 1.52
        Diamond: 2.417
        */

    };

    namespace Materials {

        Material Brass(
            Color(0.329412f, 0.223529f, 0.027451f),
            Color(0.780392f, 0.568627f, 0.113725f),
            Color(0.992157f, 0.941176f, 0.807843f), 27.89f);

        Material Gold(
            Color(0.24725f, 0.1995f, 0.0745f),
            Color(0.75164f, 0.60648f, 0.22648f),
            Color(0.628281f, 0.555802f, 0.366065f), 51.2f);

        Material Emerald(
            Color(0.0215f, 0.1745f, 0.0215f),
            Color(0.07568f, 0.61424f, 0.07568f),
            Color(0.633f, 0.727811f, 0.633f), 76.8f);

        Material Chrome(
            Color(0.25f, 0.25f, 0.25f),
            Color(0.4f, 0.4f, 0.4f),
            Color(0.774597f, 0.774597f, 0.774597f), 76.8f);

        Material Obsidian(
            Color(0.05375f, 0.05f, 0.06625f),
            Color(0.18275f, 0.17f, 0.22525f),
            Color(0.332741f, 0.328634f, 0.346435f), 38.4f);

        Material White(
            Color(1.0f),
            Color(1.0f),
            Color(1.0f), 0.0f);

		Material Black(
			Color(0.0f),
			Color(0.4f),
			Color(0.7f), 20.0f);

		Material Stripes(
			Color(1.0f),
			Color(1.0f),
			Color(1.0f), 0.0f, 0.0f, 0.0f, 1.0f, Patterns::striped);

        Material Reflective_Chrome(
            Color(0.25f, 0.25f, 0.25f),
            Color(0.4f, 0.4f, 0.4f),
            Color(0.774597f, 0.774597f, 0.774597f), 76.8f, 0.8f, 0.0f, 1.0f);


    }

}

#endif 