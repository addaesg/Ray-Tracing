#include "atom.h"

using namespace atom;

/* 
    Point
*/
Point::Point() = default;
Point::Point( double x, double y, double z): x(x), y(y), z(z)
{
    values = {x, y, z};
}

/* 
    Vector Origin
*/

VectorOrigin::VectorOrigin() = default;
VectorOrigin::VectorOrigin( double x, double y, double z): x(x), y(y), z(z)
{
    values = {x, y, z};
}


/*
    Line Origin
*/
LineOrigin::LineOrigin() = default;
LineOrigin::LineOrigin(atom::VectorOrigin v): v(v){};



/* 
    RGB
*/
Rgb::Rgb() = default;

Rgb::Rgb( uint8_t red, u_int8_t green, u_int8_t blue): r(red), g(green), b(blue)
{
    values = {r, g, b};
}


