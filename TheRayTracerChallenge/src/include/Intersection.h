#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "Vec4.h"
#include "Ray.h"

//#include "CUDAVector.cuh"

//class hittable;
class Sphere;
class Plane;
class Cube;
class Cylinder;
class Triangle;







class Observation {
private:
public:

    int shapetype, shapeid;
    float t, u, v;

    Observation() :
        shapetype(-1),
        shapeid(-1), 
        t(-1.0f), 
        u(INFINITY), 
        v(INFINITY)
    {}

    Observation(const int& shapeid, const int& shapetype, const float& t) :
        shapetype(shapetype),
        shapeid(shapeid),
        t(t),
        u(INFINITY),
        v(INFINITY)
    {}

    Observation(const int& shapeid, const int& shapetype, const float& t, const float& u, const float& v) :
        shapetype(shapetype),
        shapeid(shapeid),
        t(t),
        u(u),
        v(v)
    {}

    Observation(const Observation& other) :
        shapetype(other.shapetype),
        shapeid(other.shapeid),
        t(other.t),
        u(other.u),
        v(other.v)
    {}

    bool operator <(const Observation& other) {

 
        if (t < 0.0f) return false;
        if (other.t < 0.0f) return true;
        if (t < other.t) return true;
        return false;
    }

    Observation& operator =(const Observation& other) {
        shapetype = other.shapetype;
        shapeid = other.shapeid;
        t = other.t;
        u = other.u;
        v = other.v;
        return *this;
    }

    Observation& operator =(Observation&& other) {
        shapetype = other.shapetype;
        shapeid = other.shapeid;
        t = other.t;
        u = other.u;
        v = other.v;
        return *this;
    }

};


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