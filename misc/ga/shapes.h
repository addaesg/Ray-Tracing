#ifndef SHAPES
#define SHAPES

#include "atom.h"



namespace shapes
{
    class Solid
    {
    public:
        atom::Rgb color;
        Solid();
        ~Solid();
    }; 

    class Sphere: public Solid
    {
    public:
        struct Radius{double r = 0.0; Radius(double radius); Radius();};
        struct Equation{ 
            atom::Point center;  Sphere::Radius radius;
            std::pair<atom::Point, Sphere::Radius> values = {center, radius}; 
            Equation(atom::Point, Sphere::Radius); Equation();

        };

        Sphere::Equation equation;
        Sphere::Radius rad;
        atom::Point center;
        Sphere();
        Sphere(Sphere::Equation, atom::Rgb);
    };

    class Plane: public Solid
    {
    public:
        struct Equation{ 
            atom::Point point; 
            atom::VectorOrigin normal;
            std::pair<atom::Point, atom::VectorOrigin> values = {point, normal}; 
            Equation(atom::Point, atom::VectorOrigin); Equation();
        }
    }

}

#endif 