#include "atom.h"

using namespace atom;

/* 
    Point
*/
Point::Point() = default;
Point::Point( double x, double y, double z): x(x), y(y), z(z){};

/* 
    Vector Origin
    
*/

VectorOrigin::VectorOrigin() = default;
VectorOrigin::VectorOrigin( double x, double y, double z): x(x), y(y), z(z){};


/*
    Line Origin
*/
LineOrigin::LineOrigin() = default;
LineOrigin::LineOrigin(atom::VectorOrigin v): v(v){};



/* 
    RGB
*/
Rgb::Rgb() = default;
Rgb::Rgb( uint8_t red, uint8_t green, uint8_t blue): r(red), g(green), b(blue){};
