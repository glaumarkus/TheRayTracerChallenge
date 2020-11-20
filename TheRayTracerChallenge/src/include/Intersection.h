#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "Vec4.h"
#include "Ray.h"




class Intersection {
public:

    Observation obs[5];
    int capacity = 5;
    int current = 0;
    bool hasHit = false;


    void pushINT(const int& newid, const float& newt, const int& newShape, const float& uIN, const float& vIN) {

        /*
        Mapping shapes:
        1 = Sphere
        2 = Plane
        3 = Cube
        4 = Cylinder
        5 = Triangle
        */

        

        // only do stuff when t < 0.0f
        if (newt > 0.0f) {

            if (current == 0) { 
                obs[current++] = Observation(newid, newShape, newt, uIN, vIN); 
                hasHit = true;
                return;
            }

            for (int i = 0; i < current; i++) {
                if (newt < obs[i].t) {
                    // move all elements
                    for (int mv = current; mv > i; mv--) {
                        obs[mv] = obs[mv - 1];
                    }
                    obs[i] = Observation(newid, newShape, newt, uIN, vIN);
                    if (current < 4) current++;
                    return;
                }
            }
        }
    }

    void printOrder() {
        for (int i = 0; i < current; i++) {
            std::cout << obs[i].t <<"\n";
        }
    }

    Intersection()
    {}

    ~Intersection() 
    {}

    bool hit() {
        return hasHit;
    }

    Observation& getObservation(const int& idx) {
        return obs[idx];
    }

};






#endif