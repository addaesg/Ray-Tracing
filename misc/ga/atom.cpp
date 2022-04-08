#include "atom.h"

using namespace atom;

/* 
    point3
*/
point3::point3() = default;
point3::point3( double x, double y, double z): x(x), y(y), z(z){};

/* 
    Vector Origin

*/

vector3::vector3() = default;
vector3::vector3( double x, double y, double z): x(x), y(y), z(z){};


/*
    Line Origin
*/
line::line() = default;
line::line(atom::point3 point, atom::vector3 vector): p(point), v(vector){};



/* 
    rgb
*/
rgb::rgb() = default;
rgb::rgb( uint8_t red, uint8_t green, uint8_t blue): r(red), g(green), b(blue){};
