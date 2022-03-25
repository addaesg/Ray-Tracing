#include "atom.h"
#include "shapes.h"

using namespace shapes;


/* 
    SOLID
*/
Solid::Solid() = default;
Solid::~Solid(){};


/* 
    Sphere
*/
Sphere::Radius::Radius() = default;
Sphere::Radius::Radius(double radius): r(radius){};

Sphere::Equation::Equation() = default;
Sphere::Equation::Equation(atom::Point center, Sphere::Radius radius): center(center), radius(radius)
{
    values = {center, radius};
};

Sphere::Sphere() = default;
Sphere:::Sphere(Sphere::Equation formula, atom::Rgb color)
{
    
}
