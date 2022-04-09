#ifndef MATHUTILS 
#define MATHUTILS
#include "atom.h"

namespace vec3
{
    atom::vector3 sum(const atom::vector3 a, const atom::vector3 b);

    atom::vector3 mult(const atom::vector3 a,const double k);

    atom::vector3 cross(const atom::vector3 a, const atom::vector3 b);

    atom::vector3 fromPoints(const atom::point3 from, const atom::point3 to);

    atom::vector3 normalized(const atom::vector3 a);

    void normalizeThis(atom::vector3& a);

    double dot(const atom::vector3 a, const atom::vector3 b);
   
    double lenPow2(const atom::vector3 a);

}

namespace line3{
    atom::line fromPoints(const atom::point3 from, const atom::point3 to);
}

#endif 