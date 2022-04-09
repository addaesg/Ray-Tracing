#ifndef SHAPES  
#define SHAPES

#include "atom.h"
namespace shapes
{
    // Sphere
    class Sphere
    {
    public:
        struct equation
        {
            atom::point3 c;
            double r;
            equation();
            equation(atom::point3 c, double r);
        };
        Sphere::equation formula;
        atom::rgb color;

        Sphere();
        Sphere(Sphere::equation e, atom::rgb color);
        
        // normaliza o vetor da reta caramba
        double intersectsLine(const atom::line l);

        ~Sphere();
    };
    

    // Plane
    class Plane
    {
    public:
        struct equation
        {
            atom::point3 p;
            atom::vector3 n;
            equation();
            equation(atom::point3 p, atom::vector3 n);
        };
        Plane::equation formula;
        atom::rgb color;
        Plane();
        Plane(Plane::equation e, atom::rgb color);
        
        double intersectsLine(const atom::line l);

        ~Plane();
    };
};


#endif